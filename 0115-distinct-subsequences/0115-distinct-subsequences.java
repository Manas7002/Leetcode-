class Solution {
    public int numDistinct(String s, String t) {
        int m = s.length(), n = t.length();
        if (n > m) return 0;

        
        int[] dp = new int[n + 1];
        dp[0] = 1; 

        for (int i = 1; i <= m; i++) {
            char sc = s.charAt(i - 1);
          
            for (int j = Math.min(i, n); j >= 1; j--) {
                char tc = t.charAt(j - 1);
                if (sc == tc) {
                    dp[j] += dp[j - 1];
                }
                
            }
        }

        return dp[n];
    }
}