bool check(const char* pattern, const char* word) {
    int m = strlen(pattern);
    int n = strlen(word);
    for (int i = 0; i + m <= n; i++) {
        bool flag = true;
        for (int j = 0; j < m; j++) {
            if (word[i + j] != pattern[j]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            return true;
        }
    }
    return false;
}

int numOfStrings(char** patterns, int patternsSize, char* word) {
    int res = 0;
    for (int i = 0; i < patternsSize; i++) {
        if (check(patterns[i], word)) {
            res++;
        }
    }
    return res;
}