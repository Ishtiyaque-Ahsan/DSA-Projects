def check_hit(incoming_page, queue, occupied):
    """
    Function to check if the incoming page is already present in the frame.
    Returns True if found (Hit), otherwise False (Miss).
    """
    return incoming_page in queue[:occupied]

def print_frame(queue, occupied):
    """
    Function to print the current frame status.
    If a frame is unoccupied, it prints '-'.
    """
    for i in range(occupied):
        print(f"{queue[i]}\t\t", end="")
    print()

def lru_page_replacement(incoming_stream, frames):
    """
    Function implementing the Least Recently Used (LRU) Page Replacement algorithm.
    It keeps track of page hits, misses, and updates the frame accordingly.
    """
    n = len(incoming_stream)  # Number of page requests
    queue = [-1] * frames  # Initialize frames with -1 (empty)
    distance = [0] * frames  # Distance array for LRU replacement
    occupied = 0  # Number of occupied frames
    page_faults = 0  # Count of page faults

    print("Page\t Frame1 \t Frame2 \t Frame3")

    # Iterate through each page request in the incoming stream
    for i in range(n):
        print(f"{incoming_stream[i]}:\t\t", end="")

        # If the page is already in the frame (HIT)
        if check_hit(incoming_stream[i], queue, occupied):
            print_frame(queue, occupied)
            continue

        # If there are empty frames, place the page in an available frame
        if occupied < frames:
            queue[occupied] = incoming_stream[i]
            occupied += 1
            page_faults += 1
            print_frame(queue, occupied)
        else:
            # Use the LRU algorithm to find the least recently used page
            max_distance = float('-inf')
            index = -1

            # Calculate distance from the last appearance of each page in the frame
            for j in range(frames):
                distance[j] = 0
                for k in range(i - 1, -1, -1):
                    distance[j] += 1
                    if queue[j] == incoming_stream[k]:
                        break
                
                # Find the page with the longest distance (LRU)
                if distance[j] > max_distance:
                    max_distance = distance[j]
                    index = j

            # Replace the least recently used page
            queue[index] = incoming_stream[i]
            page_faults += 1
            print_frame(queue, occupied)

    # Display final page fault count
    print("\nTotal Page Faults:", page_faults)

# Driver Code
if __name__ == "__main__":
    # Reference page stream
    incoming_stream = [1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6]
    frames = 3  # Number of available frames

    # Call the LRU Page Replacement function
    lru_page_replacement(incoming_stream, frames)
