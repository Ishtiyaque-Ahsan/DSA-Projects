def fifo_page_replacement(incoming_stream, frames):
    """
    Function to implement the FIFO Page Replacement Algorithm.
    It keeps track of page faults, hits, and updates the frame accordingly.
    """
    page_faults = 0  # Count of page faults
    pages = len(incoming_stream)  # Number of pages in the reference string
    temp = [-1] * frames  # Initialize frames with -1 (empty)
    
    print("Incoming\tF1\tF2\tF3")

    # Iterate through each page request
    for m in range(pages):
        s = 0  # Flag to indicate a page hit (1 if hit, 0 if miss)

        # Check if the current page is already in one of the frames (Page Hit)
        for n in range(frames):
            if incoming_stream[m] == temp[n]:
                s = 1  # Page hit found
                page_faults -= 1  # Adjusting for the increment later

        page_faults += 1  # Every miss increases the page fault count

        # If there is an empty frame, place the page in the next available slot
        if page_faults <= frames and s == 0:
            temp[m] = incoming_stream[m]
        # Otherwise, replace the oldest page using FIFO logic
        elif s == 0:
            temp[(page_faults - 1) % frames] = incoming_stream[m]

        # Print the current state of the frames
        print(f"{incoming_stream[m]}\t\t", end="")
        for n in range(frames):
            print(f"{temp[n] if temp[n] != -1 else '-'}\t", end="")
        print()

    # Display the final page fault and hit counts
    print(f"\nTotal Page Faults:\t{page_faults}")
    print(f"Total Hits:\t\t{pages - page_faults}")

# Driver Code
if __name__ == "__main__":
    # Reference page stream
    incoming_stream = [1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6]
    frames = 3  # Number of available frames

    # Call the FIFO Page Replacement function
    fifo_page_replacement(incoming_stream, frames)
