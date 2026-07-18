class Solution {
    public int maxProduct(int[] nums) {
        int currentMax = nums[0];
        int currentMin = nums[0];
        int result = nums[0];

        for (int i = 1; i < nums.length; i++) {
            int candidate1 = nums[i];
            int candidate2 = currentMax * nums[i];
            int candidate3 = currentMin * nums[i];

            currentMax = Math.max(candidate1, Math.max(candidate2, candidate3));
            currentMin = Math.min(candidate1, Math.min(candidate2, candidate3));

            result = Math.max(result, currentMax);
        }

        return result;
    }
}