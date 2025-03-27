def search(key, frame_items, frame_occupied):
    """
    Function to check if a given reference (key) is already in one of the frames.
    Returns True if found (Hit), otherwise False (Miss).
    """
    return key in frame_items[:frame_occupied]

def print_outer_structure(max_frames):
    """
    Function to print the table headers.
    """
    print("Stream ", end="")
    for i in range(max_frames):
        print(f"Frame{i+1} ", end="")
    print()

def print_curr_frames(item, frame_items, frame_occupied, max_frames):
    """
    Function to print the current reference and the frame contents.
    If a frame is unoccupied, it prints '-'.
    """
    print(f"\n{item}\t", end="")
    for i in range(max_frames):
        if i < frame_occupied:
            print(f"{frame_items[i]}\t", end="")
        else:
            print("-\t", end="")
    print()

def predict(ref_str, frame_items, refStrLen, index, frame_occupied):
    """
    Function to predict the frame that will not be used for the longest time in the future.
    The function searches for each page in the frames to see when it will next be used.
    The page that is used farthest in the future is chosen for replacement.
    """
    result = -1  # Index of the frame to be replaced
    farthest = index  # Stores the farthest index where a page is found in future reference

    for i in range(frame_occupied):
        j = index
        while j < refStrLen:
            if frame_items[i] == ref_str[j]:  
                if j > farthest:
                    farthest = j
                    result = i
                break
            j += 1
        
        # If a page is never referenced again in the future, return its index immediately
        if j == refStrLen:
            return i
    
    # If no future reference is found for any frame, replace the first one (0th index)
    return 0 if result == -1 else result

def optimal_page(ref_str, refStrLen, max_frames):
    """
    Function implementing the Optimal Page Replacement algorithm.
    It keeps track of page hits, misses, and updates the frame accordingly.
    """
    frame_items = [-1] * max_frames  # Initialize frames with -1 (empty)
    frame_occupied = 0  # Tracks number of occupied frames
    hits = 0  # Count of page hits

    print_outer_structure(max_frames)  # Print table header

    # Iterate through each reference in the reference string
    for i in range(refStrLen):
        # If the page is already in a frame (HIT)
        if search(ref_str[i], frame_items, frame_occupied):
            hits += 1
            print_curr_frames(ref_str[i], frame_items, frame_occupied, max_frames)
            continue
        
        # If there are empty frames, place the page in an available frame
        if frame_occupied < max_frames:
            frame_items[frame_occupied] = ref_str[i]
            frame_occupied += 1
            print_curr_frames(ref_str[i], frame_items, frame_occupied, max_frames)
        else:
            # Use the Optimal algorithm to find which page to replace
            pos = predict(ref_str, frame_items, refStrLen, i + 1, frame_occupied)
            frame_items[pos] = ref_str[i]
            print_curr_frames(ref_str[i], frame_items, frame_occupied, max_frames)

    # Display final hit and miss count
    print("\nHits:", hits)
    print("Misses:", refStrLen - hits)

# Driver Code
if __name__ == "__main__":
    # Reference string (pages requested)
    ref_str = [7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1]
    refStrLen = len(ref_str)  # Length of reference string
    max_frames = 3  # Number of available frames

    # Call the Optimal Page Replacement function
    optimal_page(ref_str, refStrLen, max_frames)
