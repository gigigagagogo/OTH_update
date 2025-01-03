import pandas as pd
import os
import requests
from imdb import IMDb
import matplotlib.pyplot as plt
from typing import Optional, Dict, List
import textwrap
import concurrent.futures

ia = IMDb()

#api implemented in computer environment
api_key = os.getenv("TMDB_API_KEY")
rapid_key = os.getenv("RAPID_API_KEY")

# Check if API keys are present
if not api_key:
    raise ValueError("TMDB API key is missing. Please set the 'TMDB_API_KEY' environment variable!")
if not rapid_key:
    raise ValueError("RapidAPI key is missing. Please set the 'RAPID_API_KEY' environment variable!")

#Load dataframe of actors
df = pd.read_csv("./data/top_50_actors.csv")

#dictionary containing parameters for the API requests
DETAILS_PARAMS = {
    "api_key": api_key, #API key for authentication
    "language": "en-US" #language of data
}

#dictionary containing parameters for the API requests
FIND_PARAMS = {
    "api_key": api_key, #API key for authentication
    "external_source": "imdb_id"  #specify that the search is based on IMDb ID
}

#dictionary mapping menu options to corresponding functions.
#each key represents a user input (as a string), and the value is a lambda function
options = {
    "1": lambda: list_actor(),  # display the list of top 50 actors
    "2": lambda: actor_biography(get_actor_by_name()),  # show the biography of the selected actor
    "3": lambda: print_mlist(get_actor_by_name()),  # list all movies and their release years for the selected actor
    "4": lambda: actor_awards(get_actor_by_name()),
    "5": lambda: genre_movie(movie_actor(get_actor_by_name())),  # display genres of the selected actor's movies
    "6": lambda: rating_graph(movie_rating(movie_actor(get_actor_by_name()))), # show a graph of average movie ratings over the years
    "7": lambda: top_5_movies(movie_actor(get_actor_by_name())),  # show top 5 movies of the selected actor with details
    "0": lambda: print_exit()  # exit the program
}

def print_mlist(id):
    """
        Print the list of movies and their release dates for a given actor.

        Parameters:
        - id (str): IMDb ID of the actor.
    """

    #call the movie_actor function to fetch the actor's movie data using the actor's id
    movie_data = movie_actor(id)
    #check if movie_data is valid
    if movie_data:
        print("Movies and Release Dates:")
        # Sort the movies by release date in descending order (most recent first)
        sorted_movie_data = sorted(movie_data, key=lambda x: x['release_date'], reverse=True)

        # Iterate through the sorted list of movies
        for movie in sorted_movie_data:
            # Format and display the movie title and its release date
            print(f"Title: {movie['title']} - Release Date: {movie['release_date']}")
    else:
        #if no movie is found: error message
        print("No movies found for this actor.")

def print_exit():
    """
        Exit the program with a goodbye message.
    """
    print("Exiting program, Goodbye!")
    exit(0)

def menu():
    """
        Display the main menu with available options for the user.
    """
    print("*" * 65)
    print(f"0. Exit\n"
          f"1. Show list of 50 top actors\n"
          f"2. Biography\n"
          f"3. All time movie names and year\n"
          f"4. Awards\n"
          f"5. Movie genre of actor/actresses\n"
          f"6. Average rating of their movies (overall and each year)\n"
          f"7. Top 5 movies, their respective years, genre and rating")
    print("*" * 65)

def getIMDb_id(name_act: str) -> Optional[str]:
    """
        Fetch the IMDb ID of an actor by their name.

        Parameters:
        - name_act (str): Name of the actor to search for.

        Returns:
        - str: IMDb ID of the actor if found, else None.
    """

    # search for all actors with a name similar to name_act
    result = ia.search_person(name_act)

    # if not actor is found, print an error message and return None
    if not result:
        print(f'No actor was found with: {name_act}')
        return None
    # take the first result (closest to name_act) and get their imdb id
    actor_id = result[0].personID

    # return actor id with nm prefix (imdb prefix)
    return f'nm{actor_id}'

def inFrame(name: str) -> bool:
    """
        Check if an actor's name exists in the dataframe of top 50 actors.

        Parameters:
        - name (str): Name of the actor.

        Returns:
        - bool: True if the actor is in the dataframe, else False.
    """
    # convert the input name and the 'Name' column in the dataframe to lowercase and check if the name exists in the dataframe
    return name.lower() in df['Name'].str.lower().values

def list_actor() :
    """
        Print the list of top 50 actors (Position and Name).
    """
    # return Position and Name columns from the dataframe without the default Dataframe index
    print(df[['Position', 'Name']].to_string(index=False))

def translate(imdb_id: str) -> Optional[str]:
    """
        Translate an IMDb ID to a TMDb ID for the actor.

        Parameters:
        - imdb_id (str): IMDb ID of the actor.

        Returns:
        - str: TMDb ID of the actor if found, else None.
    """
    # url used to search an actor by their imdb id on tmdb
    url = f"https://api.themoviedb.org/3/find/{imdb_id}"

    try:
        # send a get request to tmdb to find the actor
        find_response = requests.get(url, params=FIND_PARAMS)
        # check the request status
        find_response.raise_for_status()
        # parse the response in a json format
        find_data = find_response.json()

        # extract actor information
        person_results = find_data.get("person_results", [])

        # if not actor is found, print an error message and return None
        if not person_results:
            print(f"No actor found with IMDb ID: {imdb_id}")
            return None

        # take the actor id
        tmdb_id = person_results[0]["id"]
        # return the tmdb actor id
        return tmdb_id

    #handle exceptions that may occur during the API request
    except requests.exceptions.RequestException as e:
        # Raise a runtime error if there is an issue with the API request
        raise RuntimeError(f"Error during the API request to URL {url}: {e}")

def retrieve_data(url: str) -> Optional[Dict]:
    """
        Retrieve data from TMDb API for a given URL.

        Parameters:
        - url (str): The API endpoint URL to fetch data from.

        Returns:
        - dict: The data retrieved from the API in JSON format.
    """
    try:
        # send a get request to tmdb to fetch data
        details_response = requests.get(url, params=DETAILS_PARAMS)
        # check the request status
        details_response.raise_for_status()
        # try to parse the response as JSON
        try:
            return details_response.json()
        except ValueError:
            print(f"Error: The response from {url} could not be parsed as JSON.")
            return None

    #handle exceptions that may occur during the API request
    except requests.exceptions.RequestException as e:
        print(f"Error during the API request to URL : {e}")
        return None

    except Exception as e:
        # Handle any other unforeseen errors
        print(f"An unexpected error occurred: {e}")
        return None

def actor_biography(imdb_id: str) :
    """
        Fetch and display the biography, birthday, and place of birth of an actor.

        Parameters:
        - imdb_id (str): IMDb ID of the actor.
    """
    tmdb_id = translate(imdb_id)
    # fetch the actor's data from TMDb
    data = retrieve_data(f"https://api.themoviedb.org/3/person/{tmdb_id}")
    if data:
        # get the actor's biography, with a default value if not available
        biography = data.get("biography", "No biography available.")
        # get the actor's birthday, with a default value if not available
        birthday = data.get("birthday", "Unknown")
        # get the actor's place of birth, with a default value if not available
        place_of_birth = data.get("place_of_birth", "Unknown")

        wrapped_biography = textwrap.fill(biography, width=80)

        # print birthday,place of birth and biography
        print(f"Biography of {data['name']}\n"
              f" Born on: {birthday}\n "
              f"Place of birth: {place_of_birth}\n "
              f"Biography: {wrapped_biography}")

def movie_actor(imdb_id: str) -> Optional[List[Dict]]:
    """
        Fetch all the movies of an actor along with their release dates.

        Parameters:
        - imdb_id (str): IMDb ID of the actor.

        Returns:
        - list: A list of dictionaries containing movie titles and release dates.
    """
    tmdb_id = translate(imdb_id)

    # fetch the data
    data = retrieve_data(f"https://api.themoviedb.org/3/person/{tmdb_id}/movie_credits")

    # list of movies with title and release date
    movie_data = [{
        "title": movie.get("title", "Null"),
        "release_date": movie.get("release_date", "Null"),
        "id": movie.get("id", "Null"),
    } for movie in data.get("cast", [])]

    return movie_data

    print(f"Error with the request: {e}")
    return None

def actor_awards(actor_id):
    """
        Fetch and display awards for an actor.

        Parameters:
        - actor_id (str): IMDb ID of the actor.
    """
    #url for fetching actor's awards
    url = "https://imdb-com.p.rapidapi.com/actor/get-awards"
    #headers for the API request, including the RapidAPI key and host
    headers = {
        "X-RapidAPI-Key": rapid_key, #API key for authentication
        "X-RapidAPI-Host": "imdb-com.p.rapidapi.com"
    }
    #dictionary with the actor's IMDb ID as a parameter
    id_dict = {"nconst": actor_id}

    try:
        #send a get request
        response = requests.get(url, headers=headers, params=id_dict)
        #check the request status
        response.raise_for_status()
        #data in json format
        data = response.json()

        #extract the list of nominations from the response
        nominations = data.get("data", {}).get("name", {}).get("awardNominations", {}).get("edges", [])

        #iterate through the nominations
        for nomination in nominations:
            #extract the award data from each nomination
            award_data = nomination.get("node", {})
            # Check if the award is won
            is_winner = award_data.get("isWinner", False)
            if is_winner:
                #Get the award name
                award_name = award_data.get("award", {}).get("awardName", "Unknown Award")
                #Get the award year
                award_year = award_data.get("award", {}).get("eventEdition", {}).get("year", "Unknown Year")

                #print award and year
                print(f"{award_year} - {award_name}")

    #handle exceptions that may occur during the API request
    except requests.exceptions.RequestException as e:
        print(f"Error fetching actor awards: {e}")

# Create a global dictionary to store the genres already retrieved during the session
genre_cache = {}
def fetch_genres(movie_ids: List[str]):
    """
        Fetch genres for all movies in parallel and store them in the cache.

        Parameters:
        - movie_ids (List[str]): List of movie IDs.

        Returns:
        - None: Updates the global genre_cache with genres for each movie.
    """
    def fetch_genre_for_movie(movie_id):
        """
            Fetch and store genre data for a single movie.

            Parameters:
            - movie_id (str): ID of the movie to fetch the genres for.

            Returns:
            - None: Updates the genre_cache with the movie's genres.
        """
        try:
            #retrieve genre data from the API for the given movie
            datam = retrieve_data(f"https://api.themoviedb.org/3/movie/{movie_id}")
            genres = datam.get("genres", []) #get the genres list or empty if not found
            #store the genre names in the cache
            genre_cache[movie_id] = [genre["name"] for genre in genres]
        except Exception as e:
            #handle errors in data retrieval
            print(f"Error fetching genres for movie ID {movie_id}: {e}")

    # Execute fetching in parallel for all movie IDs
    with concurrent.futures.ThreadPoolExecutor() as executor:
        executor.map(fetch_genre_for_movie, movie_ids)

rating_cache = {}
def fetch_ratings(movie_ids: List[str]):
    """
        Fetch average ratings for all movies in parallel and store them in the cache.

        Parameters:
        - movie_ids (List[str]): List of movie IDs.

        Returns:
        - None: Updates the global rating_cache with ratings for each movie.
    """
    def fetch_rating_for_movie(movie_id):
        """
            Fetch and store the rating data for a single movie.

            Parameters:
            - movie_id (str): ID of the movie to fetch the rating for.

            Returns:
            - None: Updates the rating_cache with the movie's rating.
        """
        try:
            #retrieve rating data from the API for the given movie
            datam = retrieve_data(f"https://api.themoviedb.org/3/movie/{movie_id}")
            rating = datam.get("vote_average", 0)  # get the avarage vote or 0 if not found
            #store the rating in the cache
            rating_cache[movie_id] = rating
        except Exception as e:
            #handle errors in data retrieval
            print(f"Error fetching ratings for movie ID {movie_id}: {e}")
    #execute fetching in parallel for all movie IDs
    with concurrent.futures.ThreadPoolExecutor() as executor:
        executor.map(fetch_rating_for_movie, movie_ids)

def genre_movie(movie_list: List[Dict]):
    """
        Fetch and display genres for each movie in the list.

        Parameters:
        - movie_list (List[Dict]): List of movie dictionaries with 'id', 'title', and 'release_date'.

        Returns:
        - None: Prints the movie titles with their respective genres.
    """
    #extract movie IDs from the movie list
    movie_ids = [movie['id'] for movie in movie_list if movie.get("id")]

    # Fetch genres in parallel for all IDs
    fetch_genres(movie_ids)

    # Display genres for each movie
    for movie in movie_list:

        title = movie.get("title", "Unknown") #get the movie title, with a default value if not available
        release_date = movie.get("release_date", "Unknown") #get the movie release date, with a default value if not available
        movie_id = movie.get("id", "Unknown") #get the movie id, with a default value if not available

        #check if movie ID is valid and fetch genres from cache
        if movie_id != "Unknown":
            genre_names = genre_cache.get(movie_id, ["Unknown"])
            #print the movie title and its genres
            print(f"{title} - ({release_date}): {', '.join(genre_names)}")
        else:
            #handle case invalid movie id
            print(f"Movie ID {movie_id} not found in cache!")

def top_5_movies(movie_list: List[Dict]):
    """
        Fetch and display the top 5 movies based on their ratings.

        Parameters:
        - movie_list (List[Dict]): List of movie dictionaries with 'id' and 'title'.

        Returns:
        - None: Prints the top 5 movies with their titles and ratings.
    """
    #extract movie IDs from the movie list
    movie_ids = [movie['id'] for movie in movie_list if movie.get("id")]

    #fetch ratings in parallel
    fetch_ratings(movie_ids)

    #sort movies by rating
    movie_list_with_ratings = [
        {"title": movie["title"], "rating": rating_cache.get(movie["id"], 0), "id": movie["id"]}
        for movie in movie_list
    ]
    #sort movies by rating in descending order
    movie_list_with_ratings.sort(key=lambda x: x["rating"], reverse=True)

    # Display top 5 movies
    top_5 = movie_list_with_ratings[:5]
    for movie in top_5:
        title = movie['title']
        rating = movie['rating']
        print(f"Title: {title} - Rating: {rating}")


def movie_rating(movie_list: Optional[List[Dict]]) -> Optional[pd.DataFrame]:
    """
        Fetch average ratings of movies over the years and return a DataFrame.

        Parameters:
        - movie_list (Optional[List[Dict]]): List of movie dictionaries with 'id' and 'release_date'.

        Returns:
        - Optional[pd.DataFrame]: DataFrame with 'year' and 'rating' columns, or None if no valid data.
    """
    movie_data = []

    #extract movie IDs from the list
    movie_ids = [movie.get("id") for movie in movie_list if movie.get("id")]

    #fetch ratings in parallel for all IDs
    fetch_ratings(movie_ids)

    #iterate through the movie list
    for movie in movie_list:
        movie_id = movie.get("id")  #get movie id

        if not movie_id:
            #handle missing movie ID
            print(f'No movie id found for {movie_id}.')
            continue

        release_date = movie.get("release_date")  #get movie release date
        year = release_date.split("-")[0] if release_date else "Unknown"

        #retrieve the rating from the cache if available
        rating = rating_cache.get(movie_id, "Null")

        if rating != "Null":
            #append the year and rating to the movie data list
            movie_data.append({
                "year": year,
                "rating": rating
            })

    #create a DataFrame from the movie data
    dataFrame = pd.DataFrame(movie_data)

    if not dataFrame.empty:
        dataFrame["year"] = pd.to_numeric(dataFrame["year"], errors="coerce")  #convert the 'year' column to numeric, handle errors
        dataFrame = dataFrame.dropna(subset=["year", "rating"])  #remove rows with missing values
        dataFrame["year"] = dataFrame["year"].astype(int)  #convert year column to integer

        #group data by year and calculate the average rating for each year
        yearly_avg = dataFrame.groupby("year")["rating"].mean().reset_index()

        #print and return the yearly average ratings
        print(yearly_avg[['year', 'rating']])
        return yearly_avg[['year', 'rating']]
    else:
        #handle case dataframe is empty
        print("Dataframe is empty!")
        return None

def rating_graph(data: Optional[pd.DataFrame]):
    """
        Plot the average rating of movies over the years.

        Parameters:
        - data (pd.DataFrame): DataFrame containing the average ratings per year.
    """
    #plot data
    plt.plot(data["year"], data["rating"])
    #set plot title
    plt.title("Average rating of their movies")
    #set x label
    plt.xlabel("Year")
    #set y label
    plt.ylabel("Mean rating of Movies")
    #display the plot
    plt.show()


def get_actor_by_name() -> Optional[str]:
    """
        Prompt the user for an actor's name and return their IMDb ID if found.

        Returns:
        - str: IMDb ID of the actor if valid, otherwise None.
    """
    print("Which actor do you need?\n")
    list_actor()

    #ask the user to input an actor's name until a valid input is provided
    while True:
        actor = input("\nEnter the actor/actress name: ").strip()

        #check if the actor is in the list
        if inFrame(actor):
            break
        print("Name not found. Please try again.")

    #get the imdb id
    imdb_id = getIMDb_id(actor)

    #if imdb id is valid return it
    if imdb_id:
        return imdb_id
    else:
        #handle case imdb id is not valid
        print(f'IMDB ID: {imdb_id} not found for any actor')
        return None

def main():
    """
        Main function that runs the program, displaying the menu and handling user input.
    """
    while True:
        #display the menu option
        menu()
        #prompt the user to select an option
        option = input("Choose an option between (0 - 7): ")
        #retrieve the corresponding action from the options dictionary
        action = options.get(option, lambda: print("Choice not available, retry!"))
        #execute the selected action
        action()

#entry point of the program
if __name__ == "__main__":
    main()