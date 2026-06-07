#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"

// Hierarchy 1: Premium Status -> Priority -> Loc_Pincode
int cmp_priority_route(const Order *a, const Order *b) {
    if (a->premium_status != b->premium_status)
        return (a->premium_status > b->premium_status) ? -1 : 1;
    if (a->priority != b->priority)
        return (a->priority < b->priority) ? -1 : 1;
    if (a->loc_pincode != b->loc_pincode)
        return (a->loc_pincode < b->loc_pincode) ? -1 : 1;
    return 0;
}

// Hierarchy 2: Premium Status -> Priority -> Order Date -> Loc_Pincode
int cmp_chronological_route(const Order *a, const Order *b) {
    if (a->premium_status != b->premium_status)
        return (a->premium_status > b->premium_status) ? -1 : 1;
    if (a->priority != b->priority)
        return (a->priority < b->priority) ? -1 : 1;
    int date_cmp = strcmp(a->order_date, b->order_date);
    if (date_cmp != 0) return date_cmp;
    if (a->loc_pincode != b->loc_pincode)
        return (a->loc_pincode < b->loc_pincode) ? -1 : 1;
    return 0;
}

static void merge(Order orders[], int left, int mid, int right, int (*compare)(const Order*, const Order*)) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Order *L = (Order*)malloc(n1 * sizeof(Order));
    Order *R = (Order*)malloc(n2 * sizeof(Order));

    // Security check for failed allocations
    if (!L || !R) {
        fprintf(stderr, "CRITICAL ERROR: Memory allocation failed during merge.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n1; i++)
        L[i] = orders[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = orders[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (compare(&L[i], &R[j]) <= 0) {
            orders[k++] = L[i++];
        } else {
            orders[k++] = R[j++];
        }
    }

    while (i < n1) orders[k++] = L[i++];
    while (j < n2) orders[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort(Order orders[], int left, int right, int (*compare)(const Order*, const Order*)) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(orders, left, mid, compare);
        merge_sort(orders, mid + 1, right, compare);
        merge(orders, left, mid, right, compare);
    }
}
