#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"

int load_orders(const char *filepath, Order orders[], int max_records) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) return -1;

    char line[256];
    int count = 0;
    int is_header = 1;

    while (fgets(line, sizeof(line), fp) && count < max_records) {
        if (is_header) {
            is_header = 0;
            continue;
        }
        // Enforce a 31-character limit to leave room for the null terminator
        sscanf(line, "%31[^,],%31[^,],%31[^,],%d,%lf,%d,%d",
               orders[count].order_id,
               orders[count].customer_name,
               orders[count].order_date,
               &orders[count].priority,
               &orders[count].amount,
               &orders[count].loc_pincode,
               &orders[count].premium_status);
        count++;
    }

    fclose(fp);
    return count;
}

int save_orders(const char *filepath, Order orders[], int n) {
    FILE *fp = fopen(filepath, "w");
    if (!fp) return -1;

    fprintf(fp, "OrderID,CustomerName,OrderDate,Priority,Amount,Pincode,Premium\n");
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%s,%s,%s,%d,%.2f,%d,%d\n",
                orders[i].order_id,
                orders[i].customer_name,
                orders[i].order_date,
                orders[i].priority,
                orders[i].amount,
                orders[i].loc_pincode,
                orders[i].premium_status);
    }

    fclose(fp);
    return 0;
}
