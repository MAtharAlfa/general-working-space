; ============================================================
; METRONOME 4/4 - UAS Orarkom 2026
; Platform  : DOSBox (DOS .COM)
; Assembler : NASM  →  nasm -f bin -o metronome.com metronome.asm
; Controls  : P = pause/resume | +/- = BPM | Q = quit
; ============================================================

    org 0x100           ; .COM entry point

; ── Constants ───────────────────────────────────────────────
BPM_DEFAULT  equ 120
BPM_MIN      equ 40
BPM_MAX      equ 240

TIMER_HZ     equ 1193182   ; PIT base frequency

; PC-Speaker ports
PORT_SPEAKER equ 0x61
PORT_PIT_CMD equ 0x43
PORT_PIT_CH2 equ 0x42

; ── Data ────────────────────────────────────────────────────
section .data

; current state
bpm         dw  BPM_DEFAULT
beat        db  1           ; 1-4
paused      db  0           ; 0=running 1=paused

; delay counter (ms per beat, updated when BPM changes)
; ms_per_beat = 60000 / BPM  — stored as 16-bit word
ms_per_beat dw  500         ; 60000/120

; ── Strings ─────────────────────────────────────────────────
str_cls     db  0x1B,'[2J',0x1B,'[H',0     ; ANSI clear + home
str_title   db  '  +-----------------------+',13,10
            db  '  |  METRONOME 4/4        |',13,10
            db  '  +-----------------------+',13,10
            db  '  | Controls:             |',13,10
            db  '  |  P  - Pause / Resume  |',13,10
            db  '  |  +  - BPM Up          |',13,10
            db  '  |  -  - BPM Down        |',13,10
            db  '  |  Q  - Quit            |',13,10
            db  '  +-----------------------+',13,10,0

str_bpm_lbl db  13,10,'  BPM : ',0
str_beat_lbl db  '  Beat: ',0
str_paused  db  '  [ PAUSED ]   ',0
str_playing db  '  [ PLAYING ]  ',0
str_newline db  13,10,0
str_dots    db  '. . . . ',0
str_beat1   db  '[1]. . . ',0
str_beat2   db  ' . [2]. . ',0
str_beat3   db  ' . . [3]. ',0
str_beat4   db  ' . . . [4]',0

; ── BSS-like area in .COM (just reserve bytes after code) ───
; (we use variables declared in .data above)

; ============================================================
; ENTRY POINT
; ============================================================
section .text

start:
    call    draw_screen         ; initial UI draw

.main_loop:
    ; ── check for keypress (non-blocking) ──
    mov     ah, 0x01            ; BIOS: check keyboard buffer
    int     0x16
    jz      .no_key             ; ZF=1 → no key

    ; consume key
    mov     ah, 0x00
    int     0x16                ; AL = ASCII

    ; jump table via comparisons (implements "jump" requirement)
    cmp     al, 'q'
    je      .do_quit
    cmp     al, 'Q'
    je      .do_quit
    cmp     al, 'p'
    je      .do_pause
    cmp     al, 'P'
    je      .do_pause
    cmp     al, '+'
    je      .do_bpm_up
    cmp     al, '-'
    je      .do_bpm_down
    jmp     .no_key

.do_quit:
    call    speaker_off
    call    clear_screen
    int     0x20                ; DOS exit

.do_pause:
    call    toggle_pause
    jmp     .no_key

.do_bpm_up:
    call    bpm_increase
    jmp     .no_key

.do_bpm_down:
    call    bpm_decrease
    jmp     .no_key

.no_key:
    ; ── if paused, loop without advancing beat ──
    cmp     byte [paused], 1
    je      .main_loop

    ; ── play one beat ──
    call    play_beat
    call    draw_beat_line

    ; ── advance beat 1→2→3→4→1 (loop requirement) ──
    inc     byte [beat]
    cmp     byte [beat], 5
    jne     .beat_ok
    mov     byte [beat], 1
.beat_ok:

    ; ── wait ms_per_beat milliseconds, polling keyboard ──
    call    wait_beat

    jmp     .main_loop

; ============================================================
; FUNCTION: draw_screen  — full UI repaint
; ============================================================
draw_screen:
    call    clear_screen
    mov     si, str_title
    call    print_str
    call    draw_bpm_line
    call    draw_status_line
    ret

; ============================================================
; FUNCTION: draw_bpm_line
; ============================================================
draw_bpm_line:
    mov     si, str_bpm_lbl
    call    print_str
    mov     ax, [bpm]
    call    print_dec       ; print BPM number
    mov     si, str_newline
    call    print_str
    ret

; ============================================================
; FUNCTION: draw_status_line  — PLAYING / PAUSED
; ============================================================
draw_status_line:
    cmp     byte [paused], 1
    je      .show_paused
    mov     si, str_playing
    call    print_str
    ret
.show_paused:
    mov     si, str_paused
    call    print_str
    ret

; ============================================================
; FUNCTION: draw_beat_line  — visual beat indicator
; ============================================================
draw_beat_line:
    ; position cursor to beat display row (row 12, col 0)
    mov     ah, 0x02
    mov     bh, 0
    mov     dh, 11          ; row 11 (0-based)
    mov     dl, 0
    int     0x10

    mov     si, str_beat_lbl
    call    print_str

    mov     al, [beat]
    cmp     al, 1
    je      .b1
    cmp     al, 2
    je      .b2
    cmp     al, 3
    je      .b3
    ; else beat 4
    mov     si, str_beat4
    call    print_str
    ret
.b1:
    mov     si, str_beat1
    call    print_str
    ret
.b2:
    mov     si, str_beat2
    call    print_str
    ret
.b3:
    mov     si, str_beat3
    call    print_str
    ret

; ============================================================
; FUNCTION: play_beat  — click via PC Speaker
;   Beat 1: higher pitch, longer  (accent)
;   Beat 2-4: lower pitch, shorter
; ============================================================
play_beat:
    cmp     byte [beat], 1
    je      .accent

    ; weak beat — ~880 Hz, 30ms
    mov     ax, 880
    call    speaker_on
    mov     cx, 30
    call    delay_ms
    call    speaker_off
    ret

.accent:
    ; strong beat — ~1760 Hz, 50ms
    mov     ax, 1760
    call    speaker_on
    mov     cx, 50
    call    delay_ms
    call    speaker_off
    ret

; ============================================================
; FUNCTION: speaker_on   AX = frequency (Hz)
; Uses PIT channel 2 + port 0x61
; ============================================================
speaker_on:
    ; AX = frequency (Hz)
    ; divisor = 1193182 / frequency
    ; We save freq in BX, compute divisor via 32-bit divide
    mov     bx, ax              ; BX = frequency

    ; program PIT channel 2, mode 3 (square wave)
    mov     al, 0xB6
    out     PORT_PIT_CMD, al

    ; compute divisor: DX:AX = 1193182, divide by BX
    mov     dx, 0x0012
    mov     ax, 0x34DE          ; 0x001234DE = 1193182
    div     bx                  ; AX = divisor

    out     PORT_PIT_CH2, al    ; low byte
    mov     al, ah
    out     PORT_PIT_CH2, al    ; high byte

    ; enable speaker gate (bits 0 and 1 of port 0x61)
    in      al, PORT_SPEAKER
    or      al, 0x03
    out     PORT_SPEAKER, al
    ret

; ============================================================
; FUNCTION: speaker_off
; ============================================================
speaker_off:
    in      al, PORT_SPEAKER
    and     al, 0xFC
    out     PORT_SPEAKER, al
    ret

; ============================================================
; FUNCTION: delay_ms   CX = milliseconds
; Uses BIOS timer tick (18.2 Hz ≈ 55ms per tick)
; For short delays we use a busy-wait calibrated loop
; ============================================================
delay_ms:
    ; busy-wait: ~1ms ≈ some inner loop count
    ; In DOSBox default cycles (~3000), tune the inner count
    ; We use BIOS int 1Ah tick counting for longer delays,
    ; and a small inner loop for <55ms precision
.outer:
    push    cx
    ; inner loop: ~1ms worth of NOPs (rough calibration)
    mov     cx, 300         ; adjust if DOSBox speed changes
.inner:
    nop
    nop
    nop
    nop
    loop    .inner
    pop     cx
    dec     cx
    jnz     .outer
    ret

; ============================================================
; FUNCTION: wait_beat
; Wait ms_per_beat ms while still polling keyboard
; Splits into 10ms chunks so keys feel responsive
; ============================================================
wait_beat:
    mov     bx, [ms_per_beat]   ; total ms to wait
.chunk:
    ; poll key
    mov     ah, 0x01
    int     0x16
    jz      .no_key_w

    ; key available — consume and handle
    mov     ah, 0x00
    int     0x16
    cmp     al, 'p'
    je      .pause_w
    cmp     al, 'P'
    je      .pause_w
    cmp     al, '+'
    je      .up_w
    cmp     al, '-'
    je      .dn_w
    cmp     al, 'q'
    je      .quit_w
    cmp     al, 'Q'
    je      .quit_w
    jmp     .no_key_w

.pause_w:
    call    toggle_pause
    ; if now paused, spin here until unpaused or quit
.pause_spin:
    cmp     byte [paused], 0
    je      .done_wait      ; unpaused → start fresh beat
    mov     ah, 0x01
    int     0x16
    jz      .pause_spin
    mov     ah, 0x00
    int     0x16
    cmp     al, 'p'
    je      .do_unpause
    cmp     al, 'P'
    je      .do_unpause
    cmp     al, 'q'
    je      .quit_w
    cmp     al, 'Q'
    je      .quit_w
    jmp     .pause_spin
.do_unpause:
    call    toggle_pause
    jmp     .done_wait

.up_w:
    call    bpm_increase
    ; recalculate remaining (just restart wait with new ms_per_beat)
    jmp     .done_wait

.dn_w:
    call    bpm_decrease
    jmp     .done_wait

.quit_w:
    call    speaker_off
    call    clear_screen
    int     0x20

.no_key_w:
    ; wait 10ms
    mov     cx, 10
    call    delay_ms
    sub     bx, 10
    jg      .chunk          ; if bx > 0 keep waiting

.done_wait:
    ret

; ============================================================
; FUNCTION: toggle_pause
; ============================================================
toggle_pause:
    xor     byte [paused], 1
    ; reposition cursor to status line and redraw it
    mov     ah, 0x02
    mov     bh, 0
    mov     dh, 10
    mov     dl, 0
    int     0x10
    call    draw_status_line
    ret

; ============================================================
; FUNCTION: bpm_increase
; ============================================================
bpm_increase:
    mov     ax, [bpm]
    cmp     ax, BPM_MAX
    jge     .no_change
    add     ax, 1
    mov     [bpm], ax
    call    recalc_ms
    call    redraw_bpm
.no_change:
    ret

; ============================================================
; FUNCTION: bpm_decrease
; ============================================================
bpm_decrease:
    mov     ax, [bpm]
    cmp     ax, BPM_MIN
    jle     .no_change
    sub     ax, 1
    mov     [bpm], ax
    call    recalc_ms
    call    redraw_bpm
.no_change:
    ret

; ============================================================
; FUNCTION: recalc_ms  — ms_per_beat = 60000 / BPM
; ============================================================
recalc_ms:
    mov     ax, 60000
    xor     dx, dx
    div     word [bpm]          ; AX = quotient = ms per beat
    mov     [ms_per_beat], ax
    ret

; ============================================================
; FUNCTION: redraw_bpm  — update BPM line in place
; ============================================================
redraw_bpm:
    mov     ah, 0x02
    mov     bh, 0
    mov     dh, 9           ; row 9 (after title block)
    mov     dl, 0
    int     0x10
    call    draw_bpm_line
    ret

; ============================================================
; FUNCTION: clear_screen
; ============================================================
clear_screen:
    mov     ax, 0x0003      ; BIOS: set 80x25 text mode (also clears)
    int     0x10
    ret

; ============================================================
; FUNCTION: print_str  SI = pointer to null-terminated string
; ============================================================
print_str:
    lodsb
    or      al, al
    jz      .done
    mov     ah, 0x0E        ; BIOS teletype
    mov     bh, 0
    int     0x10
    jmp     print_str
.done:
    ret

; ============================================================
; FUNCTION: print_dec  AX = unsigned decimal number to print
; ============================================================
print_dec:
    mov     cx, 0           ; digit counter
    mov     bx, 10
.push_loop:
    xor     dx, dx
    div     bx              ; AX = quotient, DX = remainder
    push    dx
    inc     cx
    or      ax, ax
    jnz     .push_loop
.pop_loop:
    pop     dx
    add     dl, '0'
    mov     al, dl
    mov     ah, 0x0E
    mov     bh, 0
    int     0x10
    loop    .pop_loop
    ret
