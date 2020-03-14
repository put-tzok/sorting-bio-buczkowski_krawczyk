#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int ns[] = { 501,1115,3222,5021,8762,10518,15299,19222,25301,30188 };

void fill_increasing(int *t, unsigned int n) {
    int count=0;
    for (unsigned int i = 1; i <= n; i++) {
        t[count++]=i;
    }
}

void fill_decreasing(int *t, unsigned int n) {
    int count=0;
    for (unsigned int i = n; i > 0; i--) {
        t[count++]=i;
}
}

void fill_vshape(int *t, unsigned int n) {

    int count=0;
    for (unsigned int i = n; count<(n / 2); i=i-2) {
        t[count++]=i;}
        count=n-1;
    for (unsigned int i = n-1; count>=(n/2); i=i-2) {
        t[count--]=i; }

}

void swap(int *a, int* b){
int tmpr=(*a);
(*a)=(*b);
(*b)=tmpr;
}

void selection_sort(int *t, unsigned int n) {


    for( int i=0;i<n-1;i++){
         int min=i;
        for( int j=i+1;j<n;j++) {
            if(t[j]<t[min]) min=j; }

                swap(&t[min],&t[i]);
    }
}

void insertion_sort(int *t, unsigned int n) {

    int key,x,y;

    for(x=1;x<n;x++){

        key=t[x];
        y=x-1;

         while(y>=0 && t[y]>key){

            t[y+1]=t[y];
            y=y-1;
         }
       t[y+1]=key;
    }
}

int part(int *t,int min, int r){

int x=t[r];
int i=(min-1);

for (int j = min; j <=r-1; j++)//jgvjvh
{
    if(t[j]<x){
        i++;
        swap(&t[i],&t[j]);
    }
}
i++;
swap(&t[i],&t[r]);

return i;
}

int random(int min,int r){

int diff=rand()%(r-min+1);
return min+diff;

}

int random_part(int*t,int min,int r){

int i=random(min,r);
swap(&t[i],&t[r]);
return part(t,min,r);

}

void quick_sort(int *t, unsigned int n) {

    quick_sort2(t,0,n-1);
}

void quick_sort2(int *t,int min, int r) {
    if(min<r){

        int pivot=random_part(t, min,r);

    quick_sort2(t,min,pivot-1);
    quick_sort2(t,pivot+1,r);

    } }

void heapify(int *t,int n,int i){

    int big=i;
    int left=2*i+1;
    int right=2*i+2;

    if(left<n && t[left]>t[big]){
        big=left;
    }

    if(right<n && t[right]>t[big]){
        big=right;
    }

    if(big!=i){

        swap(&t[i],&t[big]);

        heapify(t,n,big);
    }


    }

void heap_sort(int *t, unsigned int n) {

    for(int i=n/2-1;i>=0;i--){
        heapify(t,n,i);
    }

    for(int i=n-1;i>=0;i--){

        swap(&t[0],&t[i]);

        heapify(t,i,0);
    }
}

void fill_random(int *t, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        t[i] = rand();
    }
}

void is_random(int *t, unsigned int n) {
    return;
}

void is_increasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] > t[i - 1]);
    }
}

void is_decreasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] < t[i - 1]);
    }
}

void is_vshape(int *t, unsigned int n) {
    int *begin = t;
    int *end = t + n - 1;

    while (end - begin > 1) {
        assert(*begin > *end);
        begin++;
        assert(*end > *begin);
        end--;
    }
}

void is_sorted(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] >= t[i - 1]);
    }
}

void (*fill_functions[])(int *, unsigned int) = { fill_random, fill_increasing, fill_decreasing, fill_vshape };
void (*check_functions[])(int *, unsigned int) = { is_random, is_increasing, is_decreasing, is_vshape };
void (*sort_functions[])(int *, unsigned int) = { selection_sort, insertion_sort, quick_sort, heap_sort };

char *fill_names[] = { "Random", "Increasing", "Decreasing", "V-Shape" };
char *sort_names[] = { "SelectionSort", "InsertionSort", "QuickSort", "HeapSort" };

int main() {
    for (unsigned int i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions); i++) {
        void (*sort)(int *, unsigned int) = sort_functions[i];

        for (unsigned int j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++) {
            void (*fill)(int *, unsigned int) = fill_functions[j];
            void (*check)(int *, unsigned int) = check_functions[j];

            for (unsigned int k = 0; k < sizeof(ns) / sizeof(*ns); k++) {
                unsigned int n = ns[k];
                int *t = malloc(n * sizeof(*t));

                fill(t, n);
                check(t, n);

                clock_t begin = clock();
                sort(t, n);
                clock_t end = clock();
                is_sorted(t, n);

               printf("%s\t%s\t%u\t%f\n", sort_names[i], fill_names[j], n, (double)(end - begin) / (double) CLOCKS_PER_SEC);
                /*printf("%f\n",(double)(end - begin) / (double) CLOCKS_PER_SEC);*/
                free(t);
            }
        }
    }
    return 0;
}
