; ============================================================
; metronome 4/4 - UAS Orarkom 2026
; ============================================================

    org 0x100           ; .COM entry point

; ==== Constants ====
BPM_DEFAULT  equ 120
BPM_MIN      equ 40
BPM_MAX      equ 240

TIMER_HZ     equ 1193182   ; pit clock thing

; PC-Speaker ports
PORT_SPEAKER equ 0x61
PORT_PIT_CMD equ 0x43
PORT_PIT_CH2 equ 0x42

; ==== Data ====
section .data

; stuff we need to track
bpm         dw  BPM_DEFAULT
beat        db  1           ; goes 1 to 4
paused      db  0           ; 0 or 1
str_spaces  db  '   ', 0    ; 3 spaces covers 3-digit -> 2-digit shrinkage

; ms per beat, changes when bpm changes
; 60000 / bpm basically
ms_per_beat dw  500         ; default is 120bpm so 500ms


; ==== Strings ====
str_cls     db  0x1B,'[2J',0x1B,'[H',0     ; clears screen
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

section .text

start:
    call    draw_screen         ; draw the ui first

.main_loop:
    ; check if key was pressed (doesnt block)
    mov     ah, 0x01
    int     0x16
    jz      .no_key             ; nothing pressed

    ; get the key
    mov     ah, 0x00
    int     0x16                ; AL = key

    ; check each key one by one
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
    int     0x20                ; bye

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
    ; skip beat if paused
    cmp     byte [paused], 1
    je      .main_loop

    ; do a beat
    call    play_beat
    call    draw_beat_line

    ; 1->2->3->4->1->...
    inc     byte [beat]
    cmp     byte [beat], 5
    jne     .beat_ok
    mov     byte [beat], 1
.beat_ok:

    ; wait until next beat
    call    wait_beat

    jmp     .main_loop

; ============================================================
; draw_screen - redraws everything
; ============================================================
draw_screen:
    call    clear_screen
    mov     si, str_title
    call    print_str
    call    draw_bpm_line
    call    draw_status_line
    ret

; ============================================================
; draw_bpm_line - shows current bpm
; ============================================================
; ============================================================
; draw_bpm_line - shows current bpm
; ============================================================
draw_bpm_line:
    mov     si, str_bpm_lbl
    call    print_str
    mov     ax, [bpm]
    call    print_dec
    ; clear leftover chars (in case digit count shrank)
    mov     si, str_spaces
    call    print_str
    mov     si, str_newline
    call    print_str
    ret


; ============================================================
; draw_status_line - playing or paused text
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
; draw_beat_line - shows which beat we're on
; ============================================================
draw_beat_line:
    ; move cursor to beat row
    mov     ah, 0x02
    mov     bh, 0
    mov     dh, 11
    mov     dl, 0
    int     0x10

    mov     si, str_beat_lbl
    call    print_str

    ; pick the right string
    mov     al, [beat]
    cmp     al, 1
    je      .b1
    cmp     al, 2
    je      .b2
    cmp     al, 3
    je      .b3
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
; play_beat - makes the click sound
;   beat 1 is louder (higher pitch)
;   rest are quieter
; ============================================================
play_beat:
    cmp     byte [beat], 1
    je      .accent

    ; normal click
    mov     ax, 880
    call    speaker_on
    mov     cx, 30
    call    delay_ms
    call    speaker_off
    ret

.accent:
    ; beat 1, higher pitch
    mov     ax, 1760
    call    speaker_on
    mov     cx, 50
    call    delay_ms
    call    speaker_off
    ret

; ============================================================
; speaker_on - turns on the speaker at given frequency
;   AX = hz
; ============================================================
speaker_on:
    mov     bx, ax              ; save frequency

    ; set pit channel 2 to square wave mode
    mov     al, 0xB6
    out     PORT_PIT_CMD, al

    ; divisor = 1193182 / freq
    mov     dx, 0x0012
    mov     ax, 0x34DE
    div     bx

    out     PORT_PIT_CH2, al    ; low byte first
    mov     al, ah
    out     PORT_PIT_CH2, al    ; then high byte

    ; flip the speaker bits on
    in      al, PORT_SPEAKER
    or      al, 0x03
    out     PORT_SPEAKER, al
    ret

; ============================================================
; speaker_off - turns speaker off
; ============================================================
speaker_off:
    in      al, PORT_SPEAKER
    and     al, 0xFC            ; clear the bits
    out     PORT_SPEAKER, al
    ret

; ============================================================
; delay_ms - waits roughly CX milliseconds
;   uses a busy loop, not super accurate
;   tune the inner count if dosbox speed is different
; ============================================================
delay_ms:
.outer:
    push    cx
    mov     cx, 300         ; ~1ms ish
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
; wait_beat - waits ms_per_beat ms but still reads keys
;   does it in 10ms chunks
; ============================================================
wait_beat:
    mov     bx, [ms_per_beat]   ; how long to wait
.chunk:
    ; check for key during wait
    mov     ah, 0x01
    int     0x16
    jz      .no_key_w

    ; got a key, handle it
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
    ; spin here while paused
.pause_spin:
    cmp     byte [paused], 0
    je      .done_wait
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
    jmp     .done_wait      ; just restart the wait

.dn_w:
    call    bpm_decrease
    jmp     .done_wait

.quit_w:
    call    speaker_off
    call    clear_screen
    int     0x20

.no_key_w:
    ; 10ms chunk
    mov     cx, 10
    call    delay_ms
    sub     bx, 10
    jg      .chunk

.done_wait:
    ret

; ============================================================
; toggle_pause - flips the paused flag
; ============================================================
toggle_pause:
    xor     byte [paused], 1
    ; redraw the status line
    mov     ah, 0x02
    mov     bh, 0
    mov     dh, 10
    mov     dl, 0
    int     0x10
    call    draw_status_line
    ret

; ============================================================
; bpm_increase - adds 1 to bpm if not at max
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
; bpm_decrease - same but down
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
; recalc_ms - recalculate ms_per_beat from bpm
; ============================================================
recalc_ms:
    mov     ax, 60000
    xor     dx, dx
    div     word [bpm]          ; AX = ms per beat
    mov     [ms_per_beat], ax
    ret

; ============================================================
; redraw_bpm - moves cursor and redraws bpm line
; ============================================================
redraw_bpm:
    mov     ah, 0x02
    mov     bh, 0
    mov     dh, 9           ; row 9
    mov     dl, 0
    int     0x10
    call    draw_bpm_line
    ret

; ============================================================
; clear_screen - resets video mode (also clears)
; ============================================================
clear_screen:
    mov     ax, 0x0003
    int     0x10
    ret

; ============================================================
; print_str - prints null terminated string from SI
; ============================================================
print_str:
    lodsb
    or      al, al
    jz      .done
    mov     ah, 0x0E        ; bios print char
    mov     bh, 0
    int     0x10
    jmp     print_str
.done:
    ret

; ============================================================
; print_dec - prints AX as decimal
; ============================================================
print_dec:
    mov     cx, 0           ; digit count
    mov     bx, 10
.push_loop:
    xor     dx, dx
    div     bx              ; remainder goes to stack
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