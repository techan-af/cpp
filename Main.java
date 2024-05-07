import java.util.Scanner;

public class Main{
    public static void main(String args[]){
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter number of terms in array : ");
        int n = scanner.nextInt();

        System.out.println("Enter values of the array : ");

        int[] arr = new int[n];
        for(int i=0 ; i<n ; i++){
            arr[i] = scanner.nextInt();
        }

        HeapSort heapsort = new HeapSort();
        heapsort.sort(arr);

        System.out.println("Sorted array is : ");
        printArray(arr);

        scanner.close();
    }

    static void printArray(int arr[]){
        int n = arr.length;
        for(int i=0;i<n;i++){
            System.out.print(arr[i] + " ");
        }

        System.out.println();

    }
}