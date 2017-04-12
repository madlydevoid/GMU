#include <stdio.h>
#include <stdlib.h>
#include "memory_system.h"

static FILE *log_file;


main() {
  int virt_address;
  int phy_address;
  start_logging();
  
  initialize();

  printf("> ");
  scanf("%d",&virt_address);
  while (virt_address >= 0) {
     log_entry(NEW_ADDRESS,virt_address);
     phy_address = get_physical_address(virt_address);   // implement this function
/* Assumes an function returns -1 if address is illegal */
     if (phy_address != -1) {
        get_byte(phy_address);  // implement this function
     }
     printf("> ");
     scanf("%d",&virt_address);
  }
  stop_logging();
}



start_logging() {
   log_file = fopen("lab4_logfile","w");
}

stop_logging() {
   fclose(log_file);
}

/* you can add other types of logging but be sure to disable this before
 * submitting
 */

log_entry(int type, int data) {
   switch (type) {
     case NEW_ADDRESS:
  	fprintf(log_file,"Virtual Address: 0x%x \n",data); break;
     case DATA_FROM_MEMORY:
  	fprintf(log_file,"\tData: 0x%x from memory\n",data); break;
     case DATA_FROM_CACHE:
  	fprintf(log_file,"\tData: 0x%x from cache\n",data); break;
     case ADDRESS_FROM_PAGETABLE:
  	fprintf(log_file,"\tPhysical Address: 0x%x from page table\n",data); break;
     case ADDRESS_FROM_TLB:
  	fprintf(log_file,"\tPhysical Address: 0x%x from TLB\n",data); break;
     case ILLEGALVPN:
  	fprintf(log_file,"\tIllegal VPN generated: 0x%x \n",data); break;
     case PHYSICALERROR:
  	fprintf(log_file,"\tIllegal Physical Address generated: 0x%x \n",data); break;
     case ILLEGALVIRTUAL:
  	fprintf(log_file,"\tIllegal Virtual Address as input: 0x%x \n",data); break;
   }
}
