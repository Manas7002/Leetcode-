class Solution {
    public String longestPalindrome(String s) {
        String best = "";

        for (int i = 0; i < s.length(); i++) {

           
            int left = i;
            int right = i;

            while (left >= 0 && right < s.length() && s.charAt(left) == s.charAt(right)) {
                left = left - 1;
                right = right + 1;
            }
            
            String oddPalindrome = s.substring(left + 1, right);

            if (oddPalindrome.length() > best.length()) {
                best = oddPalindrome;
            }

            
            left = i;
            right = i + 1;

            while (left >= 0 && right < s.length() && s.charAt(left) == s.charAt(right)) {
                left = left - 1;
                right = right + 1;
            }
            String evenPalindrome = s.substring(left + 1, right);

            if (evenPalindrome.length() > best.length()) {
                best = evenPalindrome;
            }
        }

        return best;
    }
}