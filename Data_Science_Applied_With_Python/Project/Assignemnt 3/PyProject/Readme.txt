# Project Name: 
	Hollywood Actors and Actresses
	
# Description: 
	This project is a tool to manage and retrieve data on actors and movies using the IMDb and TMDb APIs. 
	It provides various functionalities, such as fetching actor biographies, movie details, and calculating movie ratings.

# Features:
	- Fetch detailed biographies, birthplaces, and birthdays of actors.
	- Retrieve all movies of an actor along with their release dates.
	- Analyze and visualize movie ratings over the years.
	- Display genres of movies in an actor's filmography.
	- Fetch and list awards won by an actor.
	- Identify and rank the top 5 movies of an actor based on ratings.

# How to obtain API keys:
	- TMDB:
		1. Create an account at https://www.themoviedb.org/signup and verify your email
		2. Log in, go to settings, and select API (https://www.themoviedb.org/settings/api)
		3. Generate a new API key, select 'Developer' and Approve Terms of Use
		4. Complete the required fields
	- RAPID_API:
		1. Create an account at : https://rapidapi.com/auth/sign-up
		2. Complete the required fields
		3. Subscribe to the IMDB API via this link: https://rapidapi.com/ntd119/api/imdb-com/playground/apiendpoint_9a18f24e-9787-4327-9b49-13df445a4b05 (select the basic plan)
		   (Copy the API key from the Code Snippets section on the right side of the page)
		   
# Requirments:
	1. Python 3.x or higher
	2. Internet connection for API requests
	3. Install the required dependencies:
		pip install -r dependencies.txt
	4. Set up environment variables for API keys:
		Windows:
			set TMDB_API_KEY = your_tmdb_api_key
			set RAPID_API_KEY = your_rapid_api_key
		macOS/Linux:
			export TMDB_API_KEY = your_api_key_value
			export RAPID_API_KEY = your_api_key_value
		Please note that the environment variables set using the set command (on Windows) or the export command (on macOS/Linux) are not permanent. \
		They will only persist for the duration of the current terminal session!!!
		
# Usage:
	1. Run the script:
	   python main.py
	2. Choose from the menu options to interact with the tool:
	   1. List top 50 actors
	   2. View actor biography
	   3. List movies and release years
	   4. View actor awards
	   5. View movie genres
	   6. View movie ratings by year
	   7. View top 5 movies by ratings
	   
# Contact:
	If you have any questions or suggestions, feel free to contact me at:
		robert.bararu@st.oth-regensburg.de