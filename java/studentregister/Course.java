/**
 * Stores the code, name and credits of a course.
 */

public class Course implements Comparable<Course>{
	private String code;
	private String name;
	private int credits;
	
	Course(String code, String name, int credits) {
		this.code = code;
		this.name = name;
		this.credits = credits;
	}

	public String getCode() {
		return code;
	}

	public String getName() {
		return name;
	}

	public int getCredits() {
		return credits;
	}

	@Override
	public int compareTo(Course o) {
		// TODO Auto-generated method stub
		return ((this.name).compareTo(o.name));
	}
}
