#include <stdio.h>
#include "engine.h"

int main() {
    Order orders[MAX_ORDERS];
    int n = load_orders("data/orders.csv", orders, MAX_ORDERS);

    if (n < 0) {
        fprintf(stderr, "Error: Could not load orders from data/orders.csv\n");
        return 1;
    }

    render_dashboard(orders, n);

    return 0;
}
