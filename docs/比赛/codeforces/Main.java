import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int k = sc.nextInt();
        int l = sc.nextInt();
        int m = sc.nextInt();
        int n = sc.nextInt();
        int d = sc.nextInt();
        Set<Integer> set = new HashSet<>();
        for(int i = 1; i <= d; i++) { 
            if(i % k == 0 || i % l == 0 || i % m == 0 || i % n == 0) {
                set.add(i);
            }
        }
        System.out.println(set.size());
    }
}