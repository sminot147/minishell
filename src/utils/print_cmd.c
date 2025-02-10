// void print_to(t_token *token_list)
// {
// 	while (token_list)
// 	{
// 		printf("  %s\n", token_list->token);
// 		token_list = token_list->next;
// 	}
// }

// void print_cmd(t_cmd *cmd_list)
// {
// 	while (cmd_list)
// 	{
// 		printf("========== Command ==========\n");

// 		// Arguments
// 		printf("Arguments:\n");
// 		if (cmd_list->args)
// 		{
// 			for (int i = 0; cmd_list->args[i]; i++)
// 				printf("  %s\n", cmd_list->args[i]);
// 		}
// 		else
// 			printf("  (None)\n");

// 		// Input file
// 		printf("Infile: %s\n", cmd_list->infile ? cmd_list->infile : "(None)");

// 		// Here-docs
// 		printf("Here-docs:\n");
// 		if (cmd_list->here_doc)
// 			print_to(cmd_list->here_doc);
// 		else
// 			printf("  (None)\n");

// 		// Output file
// 		printf("Outfile: %s\n", cmd_list->outfile ? cmd_list->outfile : "(None)");

// 		// Intermediate input files
// 		printf("Intermediate input files:\n");
// 		if (cmd_list->inter_file_in)
// 			print_to(cmd_list->inter_file_in);
// 		else
// 			printf("  (None)\n");

// 		// Intermediate output files
// 		printf("Intermediate output files:\n");
// 		if (cmd_list->inter_file_out)
// 			print_to(cmd_list->inter_file_out);
// 		else
// 			printf("  (None)\n");

// 		// Append flag
// 		printf("Append mode: %s\n", cmd_list->append ? "Yes" : "No");

// 		// Pipe
// 		printf("Pipe: %s\n", cmd_list->pipe ? "Yes" : "No");

// 		// Next command
// 		cmd_list = cmd_list->next;
// 		printf("\n");
// 	}
// }