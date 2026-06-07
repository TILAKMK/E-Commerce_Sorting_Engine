#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"

// Upgraded 24-bit TrueColor Palette
#define C_RST   "\x1b[0m"
#define C_HDR   "\x1b[48;2;2;6;23m\x1b[38;2;248;250;252m\x1b[1m" // Deep dark slate background (#020617), bright text
#define C_ACC   "\x1b[38;2;56;189;248m" // Vibrant sky blue accent
#define C_GRN   "\x1b[38;2;52;211;153m" // Smooth emerald green
#define C_DIM   "\x1b[38;2;148;163;184m" // Muted slate gray for borders

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void print_order_table(const char *title, Order orders[], int n) {
    printf("\n%s  === %s ===  %s\n", C_HDR, title, C_RST);
    printf(C_ACC "%-5s %-12s %-16s %-12s %-6s %-6s %-8s %-10s\n" C_RST, 
           "IDX", "ORDER ID", "CUSTOMER", "DATE", "PREM", "PRIO", "PINCODE", "AMOUNT");
    printf(C_DIM "--------------------------------------------------------------------------------\n" C_RST);
    
    for (int i = 0; i < n; i++) {
        printf("%-5d %-12s %-16s %-12s %s%-6d%s %s%-6d%s %-8d %s%-10.2f%s\n",
               i + 1,
               orders[i].order_id,
               orders[i].customer_name,
               orders[i].order_date,
               orders[i].premium_status ? C_GRN : C_DIM, orders[i].premium_status, C_RST,
               orders[i].priority == 1 ? C_GRN : C_DIM, orders[i].priority, C_RST,
               orders[i].loc_pincode,
               C_GRN, orders[i].amount, C_RST);
    }
    printf(C_DIM "--------------------------------------------------------------------------------\n" C_RST);
}

void render_dashboard(Order orders[], int n) {
    char buffer[16];
    int choice;

    while (1) {
        clear_screen();
        printf(C_HDR " E-Commerce Order Sorting Engine " C_RST "\n");
        printf(" Loaded %d records.\n\n", n);
        printf(C_ACC " [1]" C_RST " Display Raw Ingestion Stream\n");
        printf(C_ACC " [2]" C_RST " Run Regional Priority Router (Prem -> Prio -> Pin)\n");
        printf(C_ACC " [3]" C_RST " Run Global Chronological Router (Prem -> Prio -> Date -> Pin)\n");
        printf(C_ACC " [4]" C_RST " Shutdown Engine\n\n");
        
        printf("Sys_Terminal> ");
        if (!fgets(buffer, sizeof(buffer), stdin)) break;
        
        // Check if a newline is in the buffer. If not, the input was too long and we must flush stdin.
        if (!strchr(buffer, '\n')) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
        
        choice = atoi(buffer);

        if (choice == 1) {
            print_order_table("RAW INGESTION STREAM", orders, n);
        } else if (choice == 2) {
            merge_sort(orders, 0, n - 1, cmp_priority_route);
            print_order_table("REGIONAL PRIORITY MATRIX SORT", orders, n);
            save_orders("data/orders.csv", orders, n); // Persist sorted state
        } else if (choice == 3) {
            merge_sort(orders, 0, n - 1, cmp_chronological_route);
            print_order_table("GLOBAL CHRONOLOGICAL ROUTING", orders, n);
            save_orders("data/orders.csv", orders, n);
        } else if (choice == 4) {
            break;
        }

        if (choice >= 1 && choice < 4) {
            printf("\nPress Enter to continue...");
            getchar();
        }
    }
}
