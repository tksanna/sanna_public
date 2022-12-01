/**
 * Describes a course attainment as a combination of course code, 
 * student number and grade.
 */

public class Attainment {
	private String courseCode;
	private String studentNumber;
	private int grade;
	
	Attainment(String courseCode, String studentNumber, int grade) {
		this.courseCode = courseCode;
		this.studentNumber = studentNumber;
		this.grade = grade;
	}

	public String getCourseCode() {
		return courseCode;
	}

	public String getStudentNumber() {
		return studentNumber;
	}

	public int getGrade() {
		return grade;
	}
	
	
}
