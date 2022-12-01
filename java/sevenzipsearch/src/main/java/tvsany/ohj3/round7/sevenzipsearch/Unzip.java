/*
 * Handling files compressed with 7z compression by using by 
 * using the Apache Commons Compress library. 
 */

package tvsany.ohj3.round7.sevenzipsearch;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

import javax.lang.model.element.NestingKind;

import org.apache.commons.compress.archivers.sevenz.SevenZArchiveEntry;
import org.apache.commons.compress.archivers.sevenz.SevenZFile;

public class Unzip {

	public static void main(String[] args) throws IOException {
		String searchWord = args[1];
		String searchWord1UP = searchWord.substring(0, 1).toUpperCase() + searchWord.substring(1);
		searchWord = searchWord.toUpperCase();
		try (SevenZFile sf = new SevenZFile(new File(args[0]))) {

			SevenZArchiveEntry entry = sf.getNextEntry();

			while (entry != null) {
				String fname = entry.getName();
				if (!fname.contains(".txt")) {
					return;
				}
				System.out.println(fname);

				try (BufferedReader br = new BufferedReader(new InputStreamReader(sf.getInputStream(entry)))) {

					String line = null;
					int row = 0;
					while ((line = br.readLine()) != null) {
						row += 1;
						if (line.toUpperCase().contains(searchWord)) {
							String outputStr = "";
							String words[] = line.split(" ");

							for (int i = 0; i < words.length; i++) {
								String word = words[i];
								if (word.toUpperCase().equalsIgnoreCase(searchWord)) {
									word = word.toUpperCase();
								}

								if (word.toUpperCase().contains(searchWord)) {
									word = word.replace(searchWord.toLowerCase(), searchWord);
									word = word.replace(searchWord1UP, searchWord);
								}
								outputStr += " ";
								outputStr += word;

							}
							System.out.println(row + ":" + outputStr);

						}
					}
					System.out.println("");

				}
				entry = sf.getNextEntry();

			}

		}

	}

}
