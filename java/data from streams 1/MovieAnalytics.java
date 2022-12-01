import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.function.Consumer;
import java.util.stream.Stream;

public class MovieAnalytics {
	private List<Movie> list;

//	Initialises an empty movie database
	MovieAnalytics() {
		list = new ArrayList<>();
	}
	
//	returns an object that implements the interface Consumer<Movie> 
	public static Consumer<Movie> showInfo() {
		Consumer<Movie> movie = new Consumer<Movie>() {
		public void accept(Movie t){
			System.out.format("%s (By %s, %d)%n", t.getTitle(), 
					t.getDirector(), t.getReleaseYear());
		}
		};
		return movie;
	}

//	reads movie data from the file specified by the parameter.
	public void populateWithData(String fileName) 
			throws FileNotFoundException, IOException {
		try (BufferedReader file = new BufferedReader(new FileReader(fileName))) {
			String row;
			while ((row = file.readLine()) != null) {
				String[] cols = row.split(";");
				String title = cols[0];
				int releaseYear = Integer.parseInt(cols[1]);
				int duration = Integer.parseInt(cols[2]);
				String genre = cols[3];
				double score = Double.parseDouble(cols[4]);
				String director = cols[5];
				list.add(new Movie(title, releaseYear, duration, genre, score, director));
			}
		}
	}
	
//	returns a stream that lists all movies released in the year year or later
	public Stream<Movie> moviesAfter(int year){
		return list.stream()
				.filter(i -> i.getReleaseYear() >= year)
				.sorted(Comparator.comparingInt(Movie::getReleaseYear)
						.thenComparing(Movie::getTitle));
	}
//	returns a stream that lists all movies released in the year year or earlier
	public Stream<Movie> moviesBefore(int year){
		return list.stream()
				.filter(i -> i.getReleaseYear() <= year)
				.sorted(Comparator.comparingInt(Movie::getReleaseYear)
						.thenComparing(Movie::getTitle));
	}
//	returns a stream that lists all movies released between 
//	the years yearA and yearB (including also yearA and yearB)
	public Stream<Movie> moviesBetween(int yearA, int yearB) {
		return list.stream()
				.filter(i -> i.getReleaseYear() >= yearA && i.getReleaseYear() <= yearB)
				.sorted(Comparator.comparingInt(Movie::getReleaseYear)
						.thenComparing(Movie::getTitle));
	}
	
//	returns a stream that lists all movies directed by ``director
	public Stream<Movie> moviesByDirector(String director){
		return list.stream()
				.filter(i -> i.getDirector().equals(director))
				.sorted(Comparator.comparingInt(Movie::getReleaseYear)
						.thenComparing(Movie::getTitle));
		
	}

}
