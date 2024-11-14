#!/bin/bash

# Predefined values
num_factorial=5       # Value for factorial 
palindrome_str="madam"  # String palindrome
arr=(5 3 8 4 2)       # Array  bubble sort
substring="is"        # Substring to count occurrences
string="VIT is GOOD CLG"  # String for substring counting
num_sum=123           # Number for sum of digits
num_reverse=54321     # Number to reverse and check if Armstrong

factorial_rec() {
  if (( $1 <= 1 )); then
    echo 1
  else
    echo $(( $1 * $(factorial_rec $(( $1 - 1 ))) ))
  fi
}

factorial_non_rec() {
  fact=1
  for (( i=1; i<=num_factorial; i++ )); do
    fact=$(( fact * i ))
  done
  echo $fact
}

palindrome() {
  rev=$(echo "$palindrome_str" | rev)
  if [[ "$palindrome_str" == "$rev" ]]; then
    echo "$palindrome_str is a Palindrome"
  else
    echo "$palindrome_str is Not a palindrome"
  fi
}

bubble_sort() {
  sorted_arr=("${arr[@]}")
  n=${#sorted_arr[@]}
  for (( i=0; i<n-1; i++ )); do
    for (( j=0; j<n-i-1; j++ )); do
      if (( sorted_arr[j] > sorted_arr[j+1] )); then
        temp=${sorted_arr[j]}
        sorted_arr[j]=${sorted_arr[j+1]}
        sorted_arr[j+1]=$temp
      fi
    done
  done
  echo "Sorted array: ${sorted_arr[@]}"
}

count_occurrences() {
  count=$(grep -o "$substring" <<< "$string" | wc -l)
  echo "The substring '$substring' appears $count times in the string."
}

sum_of_digits() {
  num=$num_sum
  sum=0
  while (( num > 0 )); do
    sum=$(( sum + num % 10 ))
    num=$(( num / 10 ))
  done
  echo "Sum of digits of $num_sum is $sum"
}

reverse_and_armstrong() {
  num=$num_reverse
  reversed=0
  sum=0
  temp=$num

  # Reverse the number
  while (( temp > 0 )); do
    digit=$(( temp % 10 ))
    reversed=$(( reversed * 10 + digit ))
    sum=$(( sum + digit ** ${#num} ))
    temp=$(( temp / 10 ))
  done

  echo "Reversed number: $reversed"
  if (( sum == num_reverse )); then
    echo "$num_reverse is an Armstrong number"
  else
    echo "$num_reverse is not an Armstrong number"
  fi
}

# Main menu
while true; do
  echo "Choose an option:"
  echo "1. Factorial (Recursion)"
  echo "2. Factorial (Non-Recursion)"
  echo "3. Palindrome Check"
  echo "4. Bubble Sort"
  echo "5. Count Occurrences of Substring"
  echo "6. Sum of Digits"
  echo "7. Reverse and Armstrong Check"
  echo "8. Exit"
  read -p "Enter choice: " choice

  case $choice in
    1) echo "Factorial (Recursion) of $num_factorial: $(factorial_rec $num_factorial)" ;;
    2) echo "Factorial (Non-Recursion) of $num_factorial: $(factorial_non_rec)" ;;
    3) palindrome ;;
    4) bubble_sort ;;
    5) count_occurrences ;;
    6) sum_of_digits ;;
    7) reverse_and_armstrong ;;
    8) echo "Exiting..."; break ;;
    *) echo "Invalid choice. Please try again." ;;
  esac
done
