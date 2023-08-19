# STILL UNDER CONSTRUCTION


## Automated Nmap Scanning Script

This script automates running Nmap scans with various enumeration scripts against a target IP address. It provides an easy way to perform reconnaissance and vulnerability scanning.

### Features

- Runs 10 common Nmap enumeration scripts:
    - http-enum - Enumerates web directories, files, Apache mods, HTTP methods, etc.
    - smb-os-discovery - Detects OS, SMB versions, and vulnerabilities for SMB services.
    - dns-brute - Attempts to brute force DNS hostnames and subdomains.
    - dns-zone-transfer - Attempts to perform DNS zone transfers to enumerate hosts. 
    - ftp-anon - Checks for anonymous FTP access.
    - smtp-enum-users - Enumerates users by issuing RCPT TO commands. 
    - vulners - Looks up vulnerabilities associated with open ports using Vulners database.
    - snmp-brute - Attempts to brute force SNMP community strings.
    - http-vuln- - Spiders a website and attempts to find vulnerabilities.
    - smb-enum-shares - Enumerates accessible SMB shares and files.

- Scans common TCP ports such as 21, 22, 80, 139, 443, 445, etc.

- Saves output of each Nmap script to a separate file.

- Prints status messages as each script is started and completed. 

- Performs debugging and packet tracing using Nmap -d -v options.

- Creates output directory if it does not exist.

- Easy to customize scripts and ports scanned.

### Usage 

The script needs to be compiled first:

```
gcc NSE_script.c -o nmap-nse-scan
```

This generates the executable nmap-scan.

To run: 

```
sudo ./nmap-nse-scan <target IP or hostname> 
```

Root privileges are recommended so Nmap can open privileged ports.

The target IP/hostname is the only argument.

Sample output:

```
[sudo] password for user:
 
Running Nmap scans for 192.168.1.105

Starting Nmap script: http-enum
Finished Nmap script: http-enum 

Starting Nmap script: smb-os-discovery
Finished Nmap script: smb-os-discovery

...

Scans completed for 192.168.1.105
```

Results are saved in `nmap_output` folder.

### Customizing

To customize scripts and ports, modify the source:

- `nse_scripts` array contains scripts.
- Ports list in `run_nmap_with_script()`.

Recompile after changing source.

### Requirements

- Nmap installed
- NSE scripts installed 
- Linux environment

### Author

Mohsin
