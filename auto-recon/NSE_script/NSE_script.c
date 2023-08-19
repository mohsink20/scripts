#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

typedef struct {
  const char *script;
  const char *filename;  
} NSEScript;

void run_nmap_with_script(const char *ip_address, const char *script, const char *output_filename) {

  char command[512];

  snprintf(command, sizeof(command), "nmap -d -v -sV -p22,80,443,3306,21,23,25,53,110,139,389,445,1433 --script %s %s > %s",
           script, ip_address, output_filename);
           
  printf("Running command: %s\n", command);
  
  system(command);

}

void create_output_folder(const char *folder_name) {

  struct stat st;

  if (stat(folder_name, &st) == -1) {
    if (mkdir(folder_name, 0700) == -1) {
      perror("Error creating output folder");
      exit(1);
    }
  }

}


void run_nmap_for_ip(const char *ip_address, const NSEScript nse_script, const char *output_folder) {

  printf("Starting Nmap script: %s\n", nse_script.script);
  
  char output_path[256];
  snprintf(output_path, sizeof(output_path), "%s/%s", output_folder, nse_script.filename);

  run_nmap_with_script(ip_address, nse_script.script, output_path);
  
  printf("Finished Nmap script: %s\n", nse_script.script);

}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <IP address>\n", argv[0]);
    return 1;
  }

  const char *ip_address = argv[1];

  const char *output_folder = "nmap_output";
  create_output_folder(output_folder);

  printf("Running Nmap scans for IP: %s\n", ip_address);

  NSEScript nse_scripts[] = {
    {"http-enum", "http-enum.txt"},
    {"smb-os-discovery", "smb-os-discovery.txt"},
    {"dns-brute", "dns-brute.txt"},
    {"dns-zone-transfer", "dns-zone-transfer.txt"}, 
    {"ftp-anon", "ftp-anon.txt"},
    {"smtp-enum-users", "smtp-enum-users.txt"},
    {"vulners", "vulners.txt"},
    {"snmp-brute", "snmp-brute.txt"},
    {"http-vuln-", "http-vuln.txt"},
    {"smb-enum-shares", "smb-enum-shares.txt"}
  };

  for (size_t i = 0; i < sizeof(nse_scripts)/sizeof(nse_scripts[0]); ++i) {
    run_nmap_for_ip(ip_address, nse_scripts[i], output_folder);
  }

  return 0;

}
