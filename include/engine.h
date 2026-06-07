#ifndef ENGINE_H
#define ENGINE_H

#define MAX_ORDERS 10000
#define MAX_STR 32

typedef struct {
    char order_id[MAX_STR];
    char customer_name[MAX_STR];
    char order_date[MAX_STR]; 
    int priority;         // 1=Express, 2=Standard, 3=Economy
    double amount;
    int loc_pincode;
    int premium_status;   // 1=Premium, 0=Standard
} Order;

// Database Operations
int load_orders(const char *filepath, Order orders[], int max_records);
int save_orders(const char *filepath, Order orders[], int n);

// Sorting Engine
int cmp_priority_route(const Order *a, const Order *b);
int cmp_chronological_route(const Order *a, const Order *b);
void merge_sort(Order orders[], int left, int right, int (*compare)(const Order*, const Order*));

// Dashboard UI
void render_dashboard(Order orders[], int n);
void print_order_table(const char *title, Order orders[], int n);
void clear_screen();

#endif
