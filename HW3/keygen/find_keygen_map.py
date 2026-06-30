import subprocess
import string
import os

def discover_mapping_robustly():
    """
    Runs keygen.exe for each character individually to discover the mapping.
    This is a more robust method that can identify characters that are
    handled in a special way (e.g., produce no output).
    """
    # --- Configuration ---
    keygen_executable = 'keygen.exe'

    # This dictionary will store the successful mappings.
    forward_mapping = {}
    problem_chars = []

    print(f"INFO: Preparing to run '{keygen_executable}' for all 256 possible byte values.")
    print(f"INFO: This may take a moment...")

    # Iterate through all possible single-byte character values (0-255)
    for i in range(256):
        try:
            # Convert the integer value to a character.
            # This might raise an exception for values that are invalid in the system's encoding.
            char_to_test = chr(i)

            # Execute keygen.exe with a single character argument.
            result = subprocess.run(
                [keygen_executable, char_to_test],
                capture_output=True,
                text=True,
                check=True,
                encoding='latin-1' # Use an encoding that maps 0-255 directly to Unicode
            )
            output = result.stdout.strip()

            # Check if the output is a single character as expected.
            if len(output) == 1:
                forward_mapping[(i, char_to_test)] = output
            else:
                # This character is the one causing the length mismatch!
                problem_chars.append(((i, char_to_test), output))

        except FileNotFoundError:
            print(f"FATAL: '{keygen_executable}' not found. Please ensure it's in the same directory.")
            return
        except subprocess.CalledProcessError as e:
            # This can happen if the character is invalid as a command-line argument
            problem_chars.append(((i, f'char({i})'), f"ERROR: {e.stderr.strip()}"))
        except Exception as e:
            # Catch any other errors, e.g., creating the character itself
            problem_chars.append(((i, f'char({i})'), f"SCRIPT_ERROR: {e}"))

    print("\n--- ANALYSIS COMPLETE ---")

    # Report any characters that did not map correctly.
    if problem_chars:
        print("\n--- Problematic Characters Found ---")
        for (val, char_repr), out in problem_chars:
            print(f"Input: '{char_repr}' ({val}) -> Produced unexpected output: '{out}'")

    # Display the successful mappings.
    print("\n--- Discovered Forward Mapping (Input -> Output) ---")
    for i, ((val, in_char), out_char) in enumerate(forward_mapping.items()):
        print(f"'{in_char}' ({val}) -> '{out_char}'", end='   ' if (i + 1) % 4 != 0 else '\n')

if __name__ == '__main__':
    discover_mapping_robustly()