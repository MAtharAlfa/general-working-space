/*  Nama program    :   matrix_sparse_addition
    Nama            :   Muhammad Athar Alfarisi 140810250005, K.M.A.M.T. Mardova F. 140810250056, M. Faiz Nugoroho 140810250029
    NPM             :   140810250005
    Tanggal buat    :   14 Juni 2026
    Deskripsi       :   Penjumlahan dua matriks sparse yang 
                        diimplementasikan dengan multi-linked-list.
*/
#include <iostream>

struct ElementNode 
{
        int row;
        int column;
        int value;
        ElementNode* right;
        ElementNode* down;
};

struct HeaderNode 
{
        int index_value;
        HeaderNode* next_header;
        ElementNode* first_element;
};

struct SparseMatrix 
{
        int total_rows;
        int total_columns;
        HeaderNode* row_head;
        HeaderNode* column_head;
};

void createNewMatrix(SparseMatrix& matrix){ matrix = {0, 0, nullptr, nullptr}; }
void destroyMatrix(SparseMatrix& matrix);
void menu(SparseMatrix array_matrix[], SparseMatrix& result_matrix);

int main()
{
        SparseMatrix array_matrix[2], result_matrix;

        createNewMatrix(array_matrix[0]);
        createNewMatrix(array_matrix[1]);
        createNewMatrix(result_matrix);

        menu(array_matrix, result_matrix);

        destroyMatrix(array_matrix[0]);
        destroyMatrix(array_matrix[1]);
        destroyMatrix(result_matrix);

        return 0;
}

void buildHeaderList(HeaderNode*& head, int count)
{
        head = nullptr;
        HeaderNode** tail = &head;
        int index = 0;
        while (index < count)
        {
                *tail = new HeaderNode{index, nullptr, nullptr};
                tail = &((*tail)->next_header);
                index++;
        }
}

void createMatrix(SparseMatrix& matrix, int rows, int columns) 
{
        if (matrix.row_head || matrix.column_head) 
        {
                destroyMatrix(matrix);
        }
        matrix.total_rows = rows;
        matrix.total_columns = columns;
        matrix.row_head = nullptr;
        matrix.column_head = nullptr;

        buildHeaderList(matrix.row_head, rows);
        buildHeaderList(matrix.column_head, columns);
}

void insertElement(SparseMatrix& matrix, int row, int column, int value)
{
        if (value == 0)
        {
                std::cout << "Nol tidak perlu disimpan.\n";
                return;
        }

        ElementNode* new_element = new ElementNode{row, column, value, nullptr, nullptr};

        HeaderNode* current_row = matrix.row_head;
        while (current_row && current_row->index_value != row) 
        {
                current_row = current_row->next_header;
        }
        if (current_row) 
        {
                if (current_row->first_element == nullptr || current_row->first_element->column > column) 
                {
                        new_element->right = current_row->first_element;
                        current_row->first_element = new_element;
                } 
                else 
                {
                        ElementNode* temp = current_row->first_element;
                        while (temp->right && temp->right->column < column) 
                        {
                                temp = temp->right;
                        }
                        new_element->right = temp->right;
                        temp->right = new_element;
                }
        }

        HeaderNode* current_column = matrix.column_head;
        while (current_column && current_column->index_value != column) 
        {
                current_column = current_column->next_header;
        }
        if (current_column) 
        {
                if (current_column->first_element == nullptr || current_column->first_element->row > row) 
                {
                        new_element->down = current_column->first_element;
                        current_column->first_element = new_element;
                } 
                else 
                {
                        ElementNode* temp = current_column->first_element;
                        while (temp->down && temp->down->row < row) 
                        {
                                temp = temp->down;
                        }
                        new_element->down = temp->down;
                        temp->down = new_element;
                }
        }
}

void destroyMatrix(SparseMatrix& matrix)
{
        HeaderNode* current_row = matrix.row_head;
        while (current_row) 
        {
                ElementNode* current_element = current_row->first_element;
                while (current_element) 
                {
                        ElementNode* temp_element = current_element;
                        current_element = current_element->right;
                        delete temp_element;
                }
                HeaderNode* temp_row = current_row;
                current_row = current_row->next_header;
                delete temp_row;
        }

        HeaderNode* current_column = matrix.column_head;
        while (current_column) 
        {
                HeaderNode* temp_column = current_column;
                current_column = current_column->next_header;
                delete temp_column;
        }

        matrix.row_head = nullptr;
        matrix.column_head = nullptr;
        matrix.total_rows = 0;
        matrix.total_columns = 0;
}

void inputMatrix(SparseMatrix& matrix, int identifier) 
{
        int non_zero_count;
        std::cout << "\n<< Input Data Matriks ke-" << identifier + 1 << " >>\n";
        std::cout << "Masukkan jumlah elemen bukan nol: "; std::cin >> non_zero_count;

        for (int i = 0; i < non_zero_count; i++) 
        {
                int row, column, value;
                std::cout << "Data ke-" << i + 1 << " (Baris Kolom Nilai): ";
                std::cin >> row >> column >> value;

                if (row >= matrix.total_rows || column >= matrix.total_columns || row < 0 || column < 0) 
                {
                        std::cout << "Indeks matriks tidak ada, coba lagi.\n";
                        i--;
                }
                else insertElement(matrix, row, column, value);
        }
}

void drainRow(ElementNode* element, SparseMatrix& matrix_result, int row_index)
{
        while (element)
        {
                insertElement(matrix_result, row_index, element->column, element->value);
                element = element->right;
        }
}

bool addMatrices(SparseMatrix matrix_a, SparseMatrix matrix_b, SparseMatrix& matrix_result) 
{
        if (matrix_a.total_rows != matrix_b.total_rows || matrix_a.total_columns != matrix_b.total_columns) 
        {
                std::cout << "Dimensi matriks harus sama!\n";
                return false;
        }

        createMatrix(matrix_result, matrix_a.total_rows, matrix_a.total_columns);

        HeaderNode* row_a = matrix_a.row_head;
        HeaderNode* row_b = matrix_b.row_head;

        while (row_a && row_b) 
        {
                ElementNode* element_a = row_a->first_element;
                ElementNode* element_b = row_b->first_element;
                int current_row_index = row_a->index_value;

                while (element_a && element_b) 
                {
                        if (element_a->column == element_b->column) 
                        {
                                int sum_result = element_a->value + element_b->value;
                                if (sum_result != 0) 
                                {
                                        insertElement(matrix_result, current_row_index, element_a->column, sum_result);
                                }
                                element_a = element_a->right;
                                element_b = element_b->right;
                        } 
                        else if (element_a->column < element_b->column) 
                        {
                                insertElement(matrix_result, current_row_index, element_a->column, element_a->value);
                                element_a = element_a->right;
                        } 
                        else 
                        {
                                insertElement(matrix_result, current_row_index, element_b->column, element_b->value);
                                element_b = element_b->right;
                        }
                }

                drainRow(element_a, matrix_result, current_row_index);
                drainRow(element_b, matrix_result, current_row_index);

                row_a = row_a->next_header;
                row_b = row_b->next_header;
        }

        return true;
}

void printMatrix(SparseMatrix matrix) 
{
        HeaderNode* current_row = matrix.row_head;
        bool is_empty = true;

        std::cout << "Baris\tKolom\tNilai\n";
        std::cout << "------------------------\n";

        while (current_row) 
        {
                ElementNode* current_element = current_row->first_element;
                while (current_element) 
                {
                        std::cout << current_element->row << "\t" << current_element->column << "\t" << current_element->value << "\n";
                        is_empty = false;
                        current_element = current_element->right;
                }
                current_row = current_row->next_header;
        }

        if (is_empty) std::cout << "(Semua elemen bernilai nol)\n";
        std::cout << "\n";
}

void printMatrixFormatGrid(SparseMatrix matrix) 
{
        HeaderNode* current_row = matrix.row_head;
        int row_index = 0;

        while (row_index < matrix.total_rows)
        {
                ElementNode* current_element = (current_row) ? current_row->first_element : nullptr;
                int column_index = 0;

                while (column_index < matrix.total_columns)
                {
                        if (current_element && current_element->column == column_index)
                        {
                                std::cout << current_element->value << "\t";
                                current_element = current_element->right;
                        }
                        else
                        {
                                std::cout << "0\t";
                        }
                        column_index++;
                }
                std::cout << "\n";

                if (current_row) current_row = current_row->next_header;
                row_index++;
        }
        std::cout << "\n";
}

void inputSizeMatrix(SparseMatrix array_matrix[], int count) 
{
        for (int i = 0; i < count; i++) 
        {
                int rows, columns;
                std::cout << "<< Matriks ke-" << i + 1 << " >>\n";
                std::cout << "Baris : "; std::cin >> rows;
                std::cout << "Kolom : "; std::cin >> columns;
                createMatrix(array_matrix[i], rows, columns);
        }
}

void inputMatrixAll(SparseMatrix array_matrix[], int count) 
{
        for (int i = 0; i < count; i++) 
        {
                inputMatrix(array_matrix[i], i);
        }
}

void printMatrixAll(SparseMatrix array_matrix[], int count) 
{
        for (int i = 0; i < count; i++) 
        {
                std::cout << "\n=== Matriks " << i + 1 << " ===\n";
                printMatrixFormatGrid(array_matrix[i]);
        }
}

void menuDisplay() 
{
        std::cout << "=======================\n";
        std::cout << "1. Input Ukuran Matriks\n";
        std::cout << "2. Input Isi Matriks\n";
        std::cout << "3. Tampilkan Matriks\n";
        std::cout << "4. Jumlahkan Matriks\n";
        std::cout << "0. Selesai\n";
        std::cout << ": ";
}

void menu(SparseMatrix array_matrix[], SparseMatrix& result_matrix) 
{
        int matrix_count = 2;
        int choice = -1;
        bool is_size_filled = false, is_value_filled = false;
        while (choice) 
        {
                menuDisplay();
                std::cin >> choice;
                switch (choice) 
                {
                        case 1: 
                        {
                                inputSizeMatrix(array_matrix, 2);
                                is_size_filled = true;
                                is_value_filled = false;
                                break;
                        }
                        case 2:
                                if (!is_size_filled) { std::cout << "Ukuran matriks belum terdefinisi.\n"; break; }

                                inputMatrixAll(array_matrix, 2);
                                is_value_filled = true;
                                break;
                        case 3:
                                if (!is_size_filled || !is_value_filled) { std::cout << "Ukuran atau isi matriks belum terdefinisi.\n"; break; }
                                
                                printMatrixAll(array_matrix, 2);
                                break;
                        case 4: 
                        {
                                bool is_valid = ( (is_value_filled && is_size_filled) && addMatrices(array_matrix[0], array_matrix[1], result_matrix) );
                                if (is_valid) 
                                {
                                        std::cout << "Hasil penjumlahan : \n";
                                        printMatrixFormatGrid(result_matrix);
                                }
                                else 
                                {
                                        std::cout << "Matriks tidak dapat dijumlahkan.\n";
                                }
                                break;
                        }

                        case 0: std::cout << "Terimakasih.\n"; break;

                        default: std::cin.clear(); std::cin.ignore(10000, '\n');
                }
        }

        return;
}