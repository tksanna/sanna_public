/*
 * Stores the name and student number of a student.
 */

public class Student implements Comparable<Student> {
	private String name;
	private String studentNumber;
	
	public Student(String name, String studentNumber) {
		this.name = name;
		this.studentNumber = studentNumber;
	}

	public String getName() {
		return name;
	}

	public String getStudentNumber() {
		return studentNumber;
	}

	@Override
	public int compareTo(Student o) {
		return ((this.name).compareTo(o.name));
	}
	
	

}
