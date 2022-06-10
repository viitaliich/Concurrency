public class RowMultiplyWorker implements Runnable {

    private final int[][] result;
    private final int[] res;
    private int[][] matrix1;
    private int[][] matrix2;
    private final int row;

    public RowMultiplyWorker(int[][] result, int[][] matrix1, int[][] matrix2, int row, int[] res) {
        this.result = result;
        this.res = res;
        this.matrix1 = matrix1;
        this.matrix2 = matrix2;
        this.row = row;
    }

    public int min(int[] one_dimentional)
    {
        int min = one_dimentional[0];
        for (int i = 1; i < one_dimentional.length; i++){
            if (one_dimentional[i] < min){
                min = one_dimentional[i];
            }
        }
        return min;
    }

    @Override
    public void run() {

        for (int i = 0; i < matrix2[0].length; i++) {
            result[row][i] = 0;
            for (int j = 0; j < matrix1[row].length; j++) {
                result[row][i] += matrix1[row][j] * matrix2[j][i];
            }
        }
        res[row] = min(result[row]);
    }
}
