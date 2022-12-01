import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class MovieAnalytics2 {
	private List<Movie> list;

	MovieAnalytics2() {
		list = new ArrayList<>();
	}

//	reads movie data from the file specified by the parameter.
	public void populateWithData(String fileName) throws FileNotFoundException, IOException {
		try (BufferedReader file = new BufferedReader(new FileReader(fileName))) {
			file.lines()
			.map(line -> line.split(";"))
			.forEach(line -> list.add(
					new Movie(line[0], Integer.parseInt(line[1]), Integer.parseInt(line[2]),
							line[3], Double.parseDouble(line[4]), line[5])));
		}
	}

//	prints out the n directors that have directed the most movies, 
//	in descending order of the number of directed movies
	public void printCountByDirector(int n) {
		var res = list.stream()
				.collect(Collectors.groupingBy(
						Movie::getDirector, Collectors.counting())).entrySet()
				.stream()
				.sorted((o1, o2) -> o1.getKey().compareTo(o2.getKey()))
				.sorted((o1, o2) -> o2.getValue().compareTo(o1.getValue()))
				.limit(n)
				.collect(Collectors.toList());
		res.forEach(t -> System.out.println(t.getKey() + ": " + t.getValue() + " movies"));
	}

//	prints out all movie genres of the database in ascending order 
//	of the average duration of movies in that genre
	public void printAverageDurationByGenre() {
		var res = list.stream()
				.collect(Collectors.groupingBy(
						Movie::getGenre, Collectors.averagingDouble(Movie::getDuration)))
				.entrySet()
				.stream()
				.sorted((o1, o2) -> o1.getValue().compareTo(o2.getValue()))
				.collect(Collectors.toList());
//		res.forEach(t-> System.out.println(t.getKey() + ": " + t.getValue()));
		res.forEach(t-> System.out.format("%s: %.2f%n", t.getKey(), t.getValue()));
	}

//	prints out all movie genres of the database in descending order of 
//	the average rating scores of movies in that genre
	public void printAverageScoreByGenre() {
		var res = list.stream()
				.collect(Collectors.groupingBy(
						Movie::getGenre, Collectors.averagingDouble(Movie::getScore)))
				.entrySet()
				.stream()
				.sorted((o1, o2) -> o1.getKey().compareTo(o2.getKey()))
				.sorted((o1, o2) -> o2.getValue().compareTo(o1.getValue()))
				.collect(Collectors.toList());
		res.forEach(t-> System.out.format("%s: %.2f%n", t.getKey(), t.getValue()));
	}

}
