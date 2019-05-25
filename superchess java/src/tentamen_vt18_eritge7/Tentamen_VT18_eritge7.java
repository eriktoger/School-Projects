/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tentamen_vt18_eritge7;
import java.util.Scanner;
/**
 *
 * @author Erik Töger
 * eritge-7@student.ltu.se 
 */
public class Tentamen_VT18_eritge7 {

   private static Scanner input = new Scanner(System.in);
   /**
    * Den här klassen hitter möjliga rutor som två pjäser kan gå till.
    * Pjäserna är Superman (som kan gå 3 steg åt alla håll)
    * Och Korkodil som kan gå sicksack
    * 
    */
   public static void main(String[] args) {
     
      String[] spelplan;
      final int RADER = 8;
      final int KOLUMNER = 17;
      final int RUTOR = RADER * KOLUMNER ; // hur många transaktioner som ska visas.
      spelplan = new String[RUTOR]; // sätter arrayn till längd 10
      final String QUIT = "Q";
      final int RADIE = 7; // är hur långt damen kan gå
      String valet;
      char char0Pjas; // ska vara C eller S
      char char1Tecken; // ska vara :
      char char2Rad; // ska vara mellan A-rader
      char char3Kol; // ska var mellan 1-kolumn
      int char3KolInt;
      boolean rattFormat;
      
      // skulle kunna göra denna till en method
      // skapar A1,A2.. till H17. dock inte som en matris 
	 System.out.println("*****Super Chess*****");
	 System.out.println("Ange Pjäs med C(crocodile) S(superman)");
	 System.out.println("Ange Plats ex. B3 (Avsluta med Q)");
	 System.out.println("T.ex C:B3");  
      
      while(input.hasNext()){
	 
	 valet=input.next();
	 // en method som kollar
	 
	 if(valet.length()==1 & QUIT.equals(valet)){
	    break; // programmet avslutas om användaren skriver Q
	 }
	 
	 if(valet.length()==4){ // S:F6 är fyra tecken långt.
	 
	 // delar upp input i rätt delar
	 char0Pjas = valet.charAt(0);
	 char1Tecken = valet.charAt(1);
	 char2Rad = valet.charAt(2);
	 char3Kol = valet.charAt(3); // om längden är 5 så borde det finnasn en char till
	 
	 // ser så att användaren har matat in korrekt.
	 rattFormat = rattFormat(char0Pjas,char1Tecken,char2Rad,char3Kol,RADER,KOLUMNER); 
	 
	    if(rattFormat){
	    
	       skapaSpelplan(spelplan,RADER,KOLUMNER);
	
	       //rutaOrginal = Character.toString(char2Rad)+Character.toString(char3Kol);     
	       char3KolInt = Character.getNumericValue(char3Kol);
	       
	       if (char0Pjas=='S'){ // suparman är vald
		  superman(char2Rad,char3KolInt,spelplan, RADIE); // kanske bara denna som ska visas
	       } // end if S
	
	       if(char0Pjas=='C'){
		  corcodile(char2Rad,char3KolInt,spelplan);
	       } // end if C
	
	 }
	 else{
	    System.out.println("Fel input!");
	 }
	 
	 
	 }
	 else{
	    System.out.println("Fel input!");
	 }
	 
	
      } //end while input
   }// end main
   
  /**
     *
     * @param radPjasOrginal
     * @param kolPjasOrginal
     * @param spelplan
     * corcodile printer ut alla möjliga rutor som krokodilen kan hamna på
     * förutsatt att bärdet är tomt
     */ 
   
private static void corcodile(char radPjasOrginal,int kolPjasOrginal, String [] spelplan){
// korkilden kan ses som att den hoppar hage.

   /*
   Jag hann inte fixa till så att 16/17 samt G/H var beroende brädet.
   Så just nu är de hårdkodade (samt magic numbers). 
   Men jag hoppas du har överseende med detta.
   */


   String rutaOrginal = radPjasOrginal+Integer.toString(kolPjasOrginal); // rutan pjäsen står på 
   char radPjas;
   radPjas = radPjasOrginal;
   char tempRadPjas;
   int kolPjas;
   kolPjas = kolPjasOrginal;
   int tempKolPjas;
   String mojligRuta;
   boolean hittad;
   int tempKolLeft;
   int tempKolRight;
  
   char tempRadLeft; 
   char tempRadRight;
     
   tempKolPjas= kolPjas;
   tempRadPjas = radPjas;
   
   System.out.println("Möjliga Platser");
   
   // ************************ uppåt******************
   
   //uppåt enkla
   System.out.print("Uppåt: ");
   if(tempRadPjas!='A'){
   tempRadPjas--;   
   }
    //först tar vi ett steg
   
   while(true){ 
      
      mojligRuta =tempRadPjas+Integer.toString(tempKolPjas);
      hittad= hittaRuta(mojligRuta,rutaOrginal,spelplan);
    
      if(hittad){
	System.out.print(mojligRuta);
	 System.out.print(","); 
      }
      
      if(tempRadPjas == 'A' | tempRadPjas =='B'){ // // om vi landar på A/B så ska vi inte hoppa längre
	 break;
      }
      
      tempRadPjas--; // nu hoppar vi två steg
      tempRadPjas--; // om vi går uppåt på bärdet så minskar radindex (C blir D)
   
   } // end while enkla
   
   //uppåt dubbla
   
   tempKolPjas= kolPjas; 
   tempRadPjas = radPjas;
   
   tempKolLeft = kolPjas-1; //ett steg till vänster
   tempKolRight = kolPjas+1; // ett steg till höger
   
   while(true){
      if(tempRadPjas =='A' | tempRadPjas =='B'){ //vi kan inte gå uppåt
	 break;
      } 
      tempRadPjas--; // nu hoppar vi två steg direkt
      tempRadPjas--; // om vi går uppåt på bärdet så minskar radindex (C blir A)
      
      //vänstersidan
      mojligRuta =tempRadPjas+Integer.toString(tempKolLeft);
      hittad= hittaRuta(mojligRuta,rutaOrginal,spelplan);
      
      if(hittad){
	System.out.print(mojligRuta);
	 System.out.print(","); 
      }
      
      // högersidan
      mojligRuta =tempRadPjas+Integer.toString(tempKolRight);
      hittad= hittaRuta(mojligRuta,rutaOrginal,spelplan);
     
      if(hittad){
	System.out.print(mojligRuta);
	 System.out.print(","); 
      }
       
      if(tempRadPjas == 'A' | tempRadPjas =='B'){ // om vi landar på A/B så ska vi inte hoppa längre
	 break;
      }
      
      
   } // end while true lef-right
   
   
   // ************************ neråt******************
   
   System.out.println();
   System.out.print("Neråt: ");
   tempKolPjas= kolPjas; 
   tempRadPjas = radPjas;
   
    if(tempRadPjas!='H'){ // dessa borde vara beroende på brädet
   tempRadPjas++;  //först tar vi ett steg
   }
   
  
   while(true){ // om vi landar på G/H så ska vi inte hoppa längre
      
      mojligRuta =tempRadPjas+Integer.toString(tempKolPjas);
      hittad= hittaRuta(mojligRuta,rutaOrginal,spelplan);
      //System.out.println(tempRadPjas);
      if(hittad){
	System.out.print(mojligRuta);
	 System.out.print(","); 
      }
      
      if(tempRadPjas == 'G' | tempRadPjas =='H'){
	 break;
      }
      
      tempRadPjas++; // nu hoppar vi två steg
      tempRadPjas++; // om vi går uppåt på bärdet så minskar radindex (C blir D)
   
   } // end while enkla

   // neråt dubbla
   tempKolPjas= kolPjas;
   tempRadPjas = radPjas;
   
   tempKolLeft = kolPjas-1; //ett steg till vänster
   tempKolRight = kolPjas+1; // ett steg till höger
   
   while(true){
      if(tempRadPjas =='G' | tempRadPjas =='H'){ //vi kan inte gå neråt
	 break;
      } 
      tempRadPjas++; // nu hoppar vi två steg direkt
      tempRadPjas++; // om vi går uppåt på bärdet så minskar radindex (C blir D)
      
      //vänstersidan
      mojligRuta =tempRadPjas+Integer.toString(tempKolLeft);
      hittad= hittaRuta(mojligRuta,rutaOrginal,spelplan);
     
      if(hittad){
	System.out.print(mojligRuta);
	 System.out.print(","); 
      }
      
      // högersidan
      mojligRuta =tempRadPjas+Integer.toString(tempKolRight);
      hittad= hittaRuta(mojligRuta,rutaOrginal,spelplan);
      
      if(hittad){
	System.out.print(mojligRuta);
	 System.out.print(","); 
      }
      
      
      
      
   } // end neråt dubbla
   
    // ************************ höger******************
   // nu ska rader och kolumner byta plats.
   System.out.println();
   System.out.print("Höger: ");
   
   //höger enkla
   
   tempKolPjas= kolPjas; 
   tempRadPjas = radPjas;
   
   if(tempKolPjas!=17){
   tempKolPjas++;   
   }
    //först tar vi ett steg
   
   while(true){ 
     
      mojligRuta =tempRadPjas+Integer.toString(tempKolPjas);
      hittad= hittaRuta(mojligRuta,rutaOrginal,spelplan);
      //System.out.println(tempRadPjas);
      if(hittad){
	System.out.print(mojligRuta);
	 System.out.print(","); 
      }
      
      if(tempKolPjas == 16 | tempKolPjas == 17){
	 break; // om vi landar på 16/17 så ska vi inte hoppa längre
      }
      
      tempKolPjas++; // nu hoppar vi två steg
      tempKolPjas++; // om vi går uppåt på bärdet så minskar radindex (C blir D)
   
   } // end while enkla
   
   // höger dubbla
   
   
   tempKolPjas= kolPjas; 
   tempRadPjas = radPjas;
   
   tempRadLeft =radPjas;
   tempRadLeft++;//ett steg till vänster
   tempRadRight = radPjas;
   tempRadRight--;// ett steg till höger
   
   while(true){
      if(tempKolPjas == 17 | tempKolPjas == 16){ //vi kan inte gå uppåt
	 break;
      } 
      tempKolPjas++; // nu hoppar vi två steg direkt
      tempKolPjas++; // om vi går uppåt på bärdet så minskar radindex (C blir D)
      
      //vänstersidan
      mojligRuta =tempRadLeft+Integer.toString(tempKolPjas); //vänster är undersidan
      hittad= hittaRuta(mojligRuta,rutaOrginal,spelplan);
     
      if(hittad){
	System.out.print(mojligRuta);
	 System.out.print(","); 
      } 
      // högersidan
      mojligRuta =tempRadRight+Integer.toString(tempKolPjas); //höger är ovansidan
      hittad= hittaRuta(mojligRuta,rutaOrginal,spelplan);
     
      if(hittad){
	System.out.print(mojligRuta);
	 System.out.print(","); 
      }
      
   } // end höger dubbel
   
   // ************************ vänster******************
   System.out.println();
   System.out.print("Vänster: ");
   
   // nu ska rader och kolumner byta plats.
   
   //vänster enkla
   
   tempKolPjas= kolPjas; 
   tempRadPjas = radPjas;
   
   if(tempKolPjas!=1){
   tempKolPjas--;   
   }
    //först tar vi ett steg
   
   while(true){ 
     
      mojligRuta =tempRadPjas+Integer.toString(tempKolPjas);
      hittad= hittaRuta(mojligRuta,rutaOrginal,spelplan);
      //System.out.println(tempRadPjas);
      if(hittad){
	System.out.print(mojligRuta);
	 System.out.print(","); 
      }
      
      if(tempKolPjas == 1 | tempKolPjas == 2){
	 break; // om vi landar på 1/2 så ska vi inte hoppa längre
      }
      
      tempKolPjas--; // nu hoppar vi två steg
      tempKolPjas--; // om vi går uppåt på bärdet så minskar radindex (C blir D)
   
   }
   
   // Vänster dubbla
   
   tempKolPjas= kolPjas;
   tempRadPjas = radPjas;
   
   tempRadLeft =radPjas;
   tempRadLeft++;//ett steg till vänster (nedåt)
   tempRadRight = radPjas;
   tempRadRight--;// ett steg till höger (uppåt)
   
   while(true){
      if(tempKolPjas == 1 | tempKolPjas == 2){ //vi kan inte gå uppåt
	 break;
      } 
      tempKolPjas--; // nu hoppar vi två steg direkt
      tempKolPjas--; 
      
      //vänstersidan
      mojligRuta =tempRadLeft+Integer.toString(tempKolPjas); //vänster är undersidan
      hittad= hittaRuta(mojligRuta,rutaOrginal,spelplan);
     
      if(hittad){
	System.out.print(mojligRuta);
	 System.out.print(","); 
      }
      
      // högersidan
      mojligRuta =tempRadRight+Integer.toString(tempKolPjas); //höger är ovansidan
      hittad= hittaRuta(mojligRuta,rutaOrginal,spelplan);
      
      if(hittad){
	System.out.print(mojligRuta);
	 System.out.print(","); 
      }
      
      
   } // end höger dubbel
    
   
   System.out.println("");
}
   
   
   /**
     *
     * @param radPjasOrginal
     * @param kolPjasOrginal
     * @param spelplan
     * @param radie
     * Hittar de rutor ditt superman kan gå
     */
private static void superman(char radPjasOrginal,int kolPjasOrginal, String [] spelplan, int radie){
   
   String rutaOrginal = radPjasOrginal+Integer.toString(kolPjasOrginal); // rutan pjäsen står på 
   char radPjas;
   radPjas = radPjasOrginal;
   int kolPjas;
   kolPjas = kolPjasOrginal;
   int tempKolPjas;
   String mojligRuta;
   boolean hittad;
   
   System.out.println("Möjliga Platser");  
     
      for (int backIndex = 0;backIndex < (radie/2);backIndex = backIndex+1){ // radie/2 borde lyftas ut och förklars
	radPjas--; // Vid radie 3 backar vi 1 steg, radie 5 2 steg och radie 7 3 steg 
	
	kolPjas= kolPjas-1;
      }
       
      for(int radIndexS = 0;radIndexS<radie;radIndexS = radIndexS+1){
	 tempKolPjas= kolPjas;
	 
	 for(int kolIndexS = 0;kolIndexS < radie;kolIndexS = kolIndexS+1){
	    
	    mojligRuta =radPjas+Integer.toString(tempKolPjas);
	    
	    hittad= hittaRuta(mojligRuta,rutaOrginal,spelplan);
	    
	   
	    if(hittad){ // om den finns i spelplanen så ska den printas ut
	    System.out.print(mojligRuta);
	    System.out.print(",");
	    }
	    
	    
	    tempKolPjas = tempKolPjas + 1;
	 } // end for kolIndexS
	 radPjas++;
      } // end for radIndexS 
   System.out.println();
}
/**
     *
     * @param mojligRuta
     * @param rutaOrginal
     * @param spelplan
     * Kollar om rutan som vi vill gå till finns på spelplanen
     * Man får inte heller gå till ruan man står på
     */
private static boolean hittaRuta(String mojligRuta,String rutaOrginal,String[] spelplan){
 boolean hittad;
 hittad = false;
 //kollar igenom min spelplan
 for(String ruta:spelplan){
    
   if(ruta.equals(mojligRuta) ) {//istället för ==
      hittad=true;
      
      if(hittad){
	 break;
      } // end if break
      
      } // end if rutor
   } // enf for
	    
   if(mojligRuta.equals(rutaOrginal)){
   hittad=false; // rutan den står på ska inte vara med
   } 

   return hittad;
}

/**
     *
     * @param mojligRuta
     * @param rader
     * @param kolumner
     * Generar spelplanen
     */

private static void skapaSpelplan(String[] spelplan,int rader,int kolumner){
  char radBokstav = 'A';
  int kolSiffra= 1;
  String rutaString;
  int spelplanCounter;
  spelplanCounter = 0;
  
   for(int radIndex = 0;radIndex<rader;radIndex =radIndex+1){
	 if(radBokstav == 'I'){ //efter H ska vi börja om på A igen
	    radBokstav ='A';
	    }
	 
	 for (int kolIndex = 0;kolIndex < kolumner; kolIndex = kolIndex + 1){
	    rutaString = radBokstav+Integer.toString(kolSiffra);
	    spelplan[spelplanCounter]= rutaString;
	   
	    spelplanCounter = spelplanCounter +1; // istället för spC++
	    kolSiffra = kolSiffra+1; // istället för kS++
	    
	     if(kolSiffra == 18){ //efter 17 ska vi börja om på 1 igen
	    kolSiffra = 1;
	    }
	 
	 } // end for kolIndex
	 radBokstav++;// ökar char med 1 till B alltså
      } // end for radIndex
   //System.out.println("");
}
/**
     *
     * @param char0
     * @param char1
     * @param char2
     * @param char3
     * @param rader
     * @param kolumner
     * Kontrollerar att input är korrekt.
     */
private static boolean rattFormat(char char0,char char1, char char2, char char3,int rader, int kolumner){
   boolean gaVidare;
   gaVidare = true;
   int char3Int;
   char3Int= Character.getNumericValue(char3);
   String kolString;
   kolString="";
   char letter;
   letter = 'A';
   //System.out.println("Hej");
   for(int radPindex=0;radPindex < rader;radPindex = radPindex+1){
      kolString=kolString+letter;
      letter++;
      //System.out.println(letter);
   }
   //System.out.println(kolString);
   
   if (char0 !='S' & char0!='C'){
      gaVidare= false;
   }
   
   if (char1!=':'){
      gaVidare = false;
   }
   
   
   if(!kolString.contains(Character.toString(char2)) ){
      gaVidare = false;
   }
   
   if(char3Int<1 | char3Int>kolumner){
      gaVidare = false;
   }
   

return gaVidare;

} // end rattformat


} // end class Tentamen


