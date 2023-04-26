#!/bin/bash

while true; do
  read -p "$ " input

  # Handle variable replacement
  input=${input//\$\$/$$} # Replace $$ with the process ID
  input=${input//\$\?/$?} # Replace $? with the exit status of the last command

  # Execute command
  eval "$input"
done
