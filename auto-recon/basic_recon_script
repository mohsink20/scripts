#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	run_nmap_recon(const char *ip_address)
{
	char	nmap_command[512];

	// Nmap command with flags
	snprintf(nmap_command, sizeof(nmap_command),
		"sudo nmap -sS -sCV -A -T4 --script=default,vuln,safe --top-ports=1000 -p- %s", ip_address);

	printf("Running Nmap command: %s\n", nmap_command);


	// Use system() to execute nmap command
	int	result = system(nmap_command);
	if (result == -1)
	{
		perror("Error executing Nmap command");
	}
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Syntax: %s <IP address>\n", argv[0]);
		return 1;
	}

	char	*target_ip = argv[1];
	run_nmap_recon(target_ip);

	return 0;
}

