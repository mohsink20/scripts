#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	run_nmap_recon(char *ip_address)
{
	char	*args[] = {"nmap", "-sS", "-sCV", "-A", "-T4", "--script=default,vuln,safe",
				"--top-ports=1000", "-p-", NULL, NULL};
	args[9] = ip_address;

	printf("Running Nmap Reconnaissance:\n");
	FILE *output_file = fopen("nmap_log.txt", "w");
	if (output_file)
	{
		fclose(output_file);
		char command[256];
		snprintf(command, sizeof(command), "nmap -sS -sCV -A -T4 --script=default,vuln,safe --top-ports=1000 -p- %s >> nmap_log.txt 2>&1", ip_address);
		system(command);
	}
	else
	{
		fprintf(stderr, "Error opening nmap log file\n");
	}
}

void	run_ping_sweep(const char *ip_range)
{
	char	ping_sweep_command[128];
	snprintf(ping_sweep_command, sizeof(ping_sweep_command),
		"fping -g %s 2>/dev/null | grep 'is alive'", ip_range);

	printf("Running Ping Sweep:\n");
	FILE *output_file = fopen("ping_sweep_log.txt", "w");
	if (output_file)
	{
		fclose(output_file);
		char command[256];
		snprintf(command, sizeof(command), "%s >> ping_sweep_log.txt 2>&1", ping_sweep_command);
		system(command);
	}
	else
	{
		fprintf(stderr, "Error opening output file\n");
	}
}

void	run_dns_enum(const char *domain)
{
	char	dns_enum_command[128];
	snprintf(dns_enum_command, sizeof(dns_enum_command),
		"nslookup %s", domain);

	printf("Running DNS Enumeration:\n");
	FILE *output_file = fopen("dns_enum_log.txt", "w");
	if (output_file)
	{
		fclose(output_file);
		char command[256];
		snprintf(command, sizeof(command),
			"%s >> dns_enum_log.txt 2>&1", dns_enum_command);
		system(command);
	}
	else
	{
		fprintf(stderr, "Error opening output file\n");
	}
}

void	run_whois_lookup(const char *ip_address)
{
	char	whois_command[128];
	snprintf(whois_command, sizeof(whois_command),
		"whois %s", ip_address);

	printf("Running Whois Lookup:\n");
	FILE *output_file = fopen("whois_lookup_log.txt", "w");
	if (output_file)
	{
		fclose(output_file);
		char command[256];
		snprintf(command, sizeof(command), "%s >> whois_lookup_log.txt 2>&1", whois_command);
		system(command);
	}
	else
	{
		fprintf(stderr, "Error opening output file\n");
	}
}

void	run_banner_grabbing(const char *ip_address, int port)
{
	char	banner_grab_command[128];
	snprintf(banner_grab_command, sizeof(banner_grab_command),
		"echo \"\" | telnet %s %d | grep -i 'Connected to\\|Escape character'",
	ip_address, port);

	printf("Running Banner Grabbing for port %d:\n", port);
	FILE *output_file = fopen("banner_grabbing_log.txt", "w");
	if (output_file)
	{
		fclose(output_file);
		char command[256];
		snprintf(command, sizeof(command),
			"%s >> banner_grabbing_log.txt 2>&1", banner_grab_command);
		system(command);
	}
   	else
	{
		fprintf(stderr, "Error opening output file\n");
	}
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <IP address>\n", argv[0]);
		return 1;
	}

	char	*target_ip = strdup(argv[1]);
	if (target_ip == NULL)
	{
		perror("Memory allocation error");
		return 1;
	}

	int	uid = geteuid();
	if (uid != 0)
	{
		fprintf(stderr, "Error: This script must be run with root privileges.\n");
		free(target_ip);
		return 1;
 	}

	printf("Starting reconnaissance for IP: %s\n", target_ip);

	run_ping_sweep("192.168.20.0/24");
	run_dns_enum("example.com");
	run_whois_lookup(target_ip);

	int target_port = 80; // Example port for banner grabbing
	run_banner_grabbing(target_ip, target_port);

	run_nmap_recon(target_ip);

	printf("Reconnaissance completed for IP: %s\n", target_ip);

	free(target_ip);

	return 0;
}
