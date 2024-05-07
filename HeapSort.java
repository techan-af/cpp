public class HeapSort{
    public void sort(int arr[]){
        int n = arr.length;
        
        // create min heap
        for(int i = n-1 / 2; i>=0 ; i--){
            heapify(arr, i, n);
        }

        // perform heap sort
        for(int i = n-1 ; i>0 ; i--){
            int temp = arr[i];
            arr[i] = arr[0];
            arr[0] = temp;

            heapify(arr, 0, i);
        }
    } 

    void heapify(int arr[], int i, int n){
        int largest = i;
        int left = 2*i + 1;
        int right = 2*i + 2;

        if(left<n && arr[left]>arr[largest]){
            largest = left;
        }

        if(right<n && arr[right]>arr[largest]){
            largest = right;
        }

        if(largest != i){
            int temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;
            
            heapify(arr, largest, n);
        }
    }
}