import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;

class Solution {
    public List<List<String>> groupAnagrams(String[] strs) {
        HashMap<String, List<String>> map = new HashMap<>();

        for (int i = 0; i < strs.length; i++) {
            String currentWord = strs[i];

            char[] chars = currentWord.toCharArray();
            Arrays.sort(chars);
            String key = new String(chars);

            boolean keyExists = map.containsKey(key);

            if (keyExists == false) {
                List<String> newList = new ArrayList<>();
                map.put(key, newList);
            }

            List<String> bucket = map.get(key);
            bucket.add(currentWord);
        }

        List<List<String>> result = new ArrayList<>();
        for (String key : map.keySet()) {
            result.add(map.get(key));
        }

        return result;
    }
}