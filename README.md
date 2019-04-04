# Four-Russians-Algorithm

- matrix is vector<vector< T >> where T is uint16_t or uint64_t

- template< typename T >
void get(matrix< T >& M) - initialize empty matrix from console input
  
- template< typename Cast = uint16_t, typename T >
void print(matrix< T >& M) - prints matrix to the standart output. Casting each element to a specific type can be done by changing typename Cast
  
- void preprocessVectors(int length) - generates matrix of all multiply combinations of length-sized vectors

- uint64_t readHorizontalVec(matrix< uint16_t >& M, int row, int column, int length) - reads length-sized ector from matrix on specific row which begins on specific column

- uint64_t readVerticalVec(matrix< uint16_t >& M, int row, int column, int length) - reads length-sized ector from matrix on specific column which begins on specific row

- matrix< uint64_t > preprocessMatrix(matrix< uint16_t >& M, int k, bool useLines) - creates a new matrix with k-sized vectors as elements. If useLines is true, vectors are horizontal, if false - vertical

- matrix< uint16_t > multiply(matrix< uint64_t >& A, matrix< uint64_t >& B) - creates a new matrix as a result of multiply A and B matrices. A and B should be preprocessed and preprocess Vectors should be called before.
