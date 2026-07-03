#define MIN_QUEUE_SIZE 64

typedef struct Element {
    int data[2];
} Element;

typedef bool (*compare)(const void*, const void*);

typedef struct PriorityQueue {
    Element* arr;
    int capacity;
    int queueSize;
    compare lessFunc;
} PriorityQueue;

Element* createElement(int x, int y) {
    Element* obj = (Element*)malloc(sizeof(Element));
    obj->data[0] = x;
    obj->data[1] = y;
    return obj;
}

static bool less(const void* a, const void* b) {
    Element* e1 = (Element*)a;
    Element* e2 = (Element*)b;
    return e1->data[0] > e2->data[0] ||
           (e1->data[0] == e2->data[0] && e1->data[1] > e2->data[1]);
}

static bool greater(const void* a, const void* b) {
    Element* e1 = (Element*)a;
    Element* e2 = (Element*)b;
    return e1->data[0] < e2->data[0];
}

static void memswap(void* m1, void* m2, size_t size) {
    unsigned char* a = (unsigned char*)m1;
    unsigned char* b = (unsigned char*)m2;
    while (size--) {
        *b ^= *a ^= *b ^= *a;
        a++;
        b++;
    }
}

static void swap(Element* arr, int i, int j) {
    memswap(&arr[i], &arr[j], sizeof(Element));
}

static void down(Element* arr, int size, int i, compare cmpFunc) {
    for (int k = 2 * i + 1; k < size; k = 2 * k + 1) {
        if (k + 1 < size && cmpFunc(&arr[k], &arr[k + 1])) {
            k++;
        }
        if (cmpFunc(&arr[k], &arr[(k - 1) / 2])) {
            break;
        }
        swap(arr, k, (k - 1) / 2);
    }
}

PriorityQueue* createPriorityQueue(compare cmpFunc) {
    PriorityQueue* obj = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    obj->capacity = MIN_QUEUE_SIZE;
    obj->arr = (Element*)malloc(sizeof(Element) * obj->capacity);
    obj->queueSize = 0;
    obj->lessFunc = cmpFunc;
    return obj;
}

void heapfiy(PriorityQueue* obj) {
    for (int i = obj->queueSize / 2 - 1; i >= 0; i--) {
        down(obj->arr, obj->queueSize, i, obj->lessFunc);
    }
}

void enQueue(PriorityQueue* obj, Element* e) {
    if (obj->queueSize == obj->capacity) {
        obj->capacity *= 2;
        obj->arr = realloc(obj->arr, sizeof(Element) * obj->capacity);
    }
    memcpy(&obj->arr[obj->queueSize], e, sizeof(Element));
    for (int i = obj->queueSize;
         i > 0 && obj->lessFunc(&obj->arr[(i - 1) / 2], &obj->arr[i]);
         i = (i - 1) / 2) {
        swap(obj->arr, i, (i - 1) / 2);
    }
    obj->queueSize++;
}

Element* deQueue(PriorityQueue* obj) {
    swap(obj->arr, 0, obj->queueSize - 1);
    down(obj->arr, obj->queueSize - 1, 0, obj->lessFunc);
    Element* e = &obj->arr[obj->queueSize - 1];
    obj->queueSize--;
    return e;
}

bool isEmpty(const PriorityQueue* obj) { return obj->queueSize == 0; }

Element* front(const PriorityQueue* obj) {
    if (obj->queueSize == 0) return NULL;
    return &obj->arr[0];
}

void clear(PriorityQueue* obj) { obj->queueSize = 0; }

int size(const PriorityQueue* obj) { return obj->queueSize; }

void freeQueue(PriorityQueue* obj) {
    free(obj->arr);
    free(obj);
}

typedef struct {
    int to;
    int weight;
} Edge;

typedef struct {
    Edge* data;
    int size;
    int capacity;
} Vector;

static void addEdge(Vector* vec, int to, int weight) {
    if (vec->size == vec->capacity) {
        vec->capacity = (vec->capacity == 0) ? 4 : vec->capacity * 2;
        vec->data = (Edge*)realloc(vec->data, sizeof(Edge) * vec->capacity);
    }
    vec->data[vec->size].to = to;
    vec->data[vec->size].weight = weight;
    vec->size++;
}

static bool check(int mid, Vector* graph, int n, long long k) {
    long long* dis = (long long*)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        dis[i] = LLONG_MAX;
    }
    PriorityQueue* pq = createPriorityQueue(less);
    dis[0] = 0;
    Element start = {{0, 0}};
    enQueue(pq, &start);

    bool result = false;
    while (!isEmpty(pq)) {
        Element top = *front(pq);
        deQueue(pq);

        long long d = top.data[0];
        int u = top.data[1];

        if (d > k) {
            result = false;
            break;
        }
        if (u == n - 1) {
            result = true;
            break;
        }
        if (d > dis[u]) {
            continue;
        }
        for (int i = 0; i < graph[u].size; i++) {
            int v = graph[u].data[i].to;
            int w = graph[u].data[i].weight;
            if (w < mid) continue;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                Element e = {{(int)dis[v], v}};
                enQueue(pq, &e);
            }
        }
    }

    free(dis);
    freeQueue(pq);
    return result;
}

int findMaxPathScore(int** edges, int edgesSize, int* edgesColSize,
                     bool* online, int n, long long k) {
    Vector* graph = (Vector*)malloc(n * sizeof(Vector));
    for (int i = 0; i < n; i++) {
        graph[i].data = NULL;
        graph[i].size = 0;
        graph[i].capacity = 0;
    }

    int l = INT_MAX, r = 0;
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        if (!online[u] || !online[v]) {
            continue;
        }
        addEdge(&graph[u], v, w);
        l = fmin(l, w);
        r = fmax(r, w);
    }

    if (!check(l, graph, n, k)) {
        for (int i = 0; i < n; i++) {
            free(graph[i].data);
        }
        free(graph);
        return -1;
    }

    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (check(mid, graph, n, k)) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    for (int i = 0; i < n; i++) {
        free(graph[i].data);
    }
    free(graph);
    return r;
}