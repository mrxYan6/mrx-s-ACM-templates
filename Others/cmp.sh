#!/bin/zsh

# Assuming your CPP executable is named "your_cpp_executable"
cpp_executable="../C"

# Function to compare two files
function compare_files {
    diff_output=$(diff -w "$1" "$2")
    if [ -n "$diff_output" ]; then
        echo "Error: Output mismatch for $1 and $2"
        echo "$diff_output"
    else
        echo "Test Passed: $1 and $2"
    fi
}

# Loop through the test cases from 1.in to 37.in
for i in {1..32}; do
    input_file="${i}.in"
    output_file="${i}.out"
    expected_output_file="${i}.out"

    # Execute the CPP code with input_file and capture the output in result_out
    result_out=$($cpp_executable < $input_file)

    # Create a temporary file for storing the result output
    tmp_result_file="/tmp/result_${i}.out"
    echo "$result_out" > "$tmp_result_file"

    # Compare the result with the expected output
    compare_files "$tmp_result_file" "$expected_output_file"

    # Remove the temporary file
    rm "$tmp_result_file"
done
