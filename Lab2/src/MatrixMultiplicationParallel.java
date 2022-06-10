import java.util.Date;

public class MatrixMultiplicationParallel {

    public static void main(String[] args) {

        Date start = new Date();

        int[][] m1 = MatrixGeneratorUtil.generateMatrix(2000, 1000);
        int[][] m2 = MatrixGeneratorUtil.generateMatrix(1000, 2000);

        int[][] result = new int[m1.length][m2[0].length];
        int[] res = new int[m1.length];
        ParallelThreadsCreator.multiply(m1, m2, result, res);

        int min = res[0];
        for (int i = 1; i < res.length; i++){
            if (res[i] < min){
                min = res[i];
            }
        }

        Date end = new Date();
        System.out.println("\nTime taken in milli seconds: " + (end.getTime() - start.getTime()));
    }
}
