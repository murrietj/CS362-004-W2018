

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
       boolean result;
       UrlValidator urlValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);


       //Create urls and their expected results from UrlValidator.isValid()
       String[] testUrls = {"http://www.google.com",
                            "http:/www.google.com",
                            "http//www.google.com",
                            "www.google.com",
                            "www.google",
                            "google.com",
                            "google.com/foo",
                            "google.com/file?foo=bar",
                            "255.255.255.255",
                            ""};
       boolean[] expectedResults = {true,
                                    false,
                                    false,
                                    true,
                                    false,
                                    true,
                                    true,
                                    false,
                                    true,
                                    false};
       
       //Test UrlValidator.isValid() with all the urls we created
       for(int i = 0; i < testUrls.length; i++)
       {
           result = urlValidator.isValid(testUrls[i]);
           
           //assertTrue(result == expectedResults[i]);
           if(result == expectedResults[i])
           {
               System.out.format("Test SUCCESSFUL for url: %s\n", testUrls[i]);
           }
           else
           {
               System.out.format("Test FAILED for url: '%s'. ", testUrls[i]);
               if(expectedResults[i])
               {
                   System.out.format("Expected valid but got invalid.\n", testUrls[i]);
               }
               else
               {
                   System.out.format("Expected invalid but got valid.\n", testUrls[i]);
               }
           }
       }
   }
   
   // URL can be fined as scheme://authority
   public void testYourFirstPartition()
   {
	   // testing schemes
	   UrlValidator urlValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String[] validSchemes = {"http://", ""};
	   String[] invalidSchemes = { "3ht://", "http:/", "http:", "http/", "://"};
	   String domain = "www.google.com";
	   boolean result = true;
	   
	   String validUrl;
	   String invalidUrl;

	   System.out.println("Test First Partition Begin");
	   	   
	   for (String scheme : validSchemes)  {
		   validUrl = scheme + domain;
		   if (!urlValidator.isValid(validUrl)) {
			   System.out.println("INCORRECT: " + validUrl + " as invalid should be valid");
			   result = false;
		   }
	   }
	   
	   for (String scheme : invalidSchemes)  {
		   invalidUrl = scheme + domain;
		   if (urlValidator.isValid(invalidUrl)) {
			   System.out.println("INCORRECT: " + invalidUrl + " as valid should be invalid") ;
			   result = false;
		   }
	   }
	   
	   if (result) {
		   System.out.println("Testing First Partition: Scheme Passed");
	   } else {
		   System.out.println("Testing First Partition: Valid Scheme Failed");
	   }
	   
	   System.out.println("Test First Partition End");
   }
   
   public void testYourSecondPartition(){
	   // testing authority
	   UrlValidator urlValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String validSchemes = "http://";
	   String[] validDomains = {"www.google.com", "google.com", "0.0.0.0", "255.255.255.255"};
	   String[] invalidDomains = {"google", ".google.com", "www.google."};
	   boolean result = true;
	   
	   String validUrl;
	   String invalidUrl;

	   System.out.println("Test Second Partition Begin");
	   	   
	   for (String domain : validDomains)  {
		   validUrl = validSchemes + domain;
		   if (!urlValidator.isValid(validUrl)) {
			   System.out.println("INCORRECT: " + validUrl + " as invalid should be valid");
			   result = false;
		   }
	   }
	   
	   for (String domain : invalidDomains)  {
		   invalidUrl = validSchemes + domain;
		   if (urlValidator.isValid(invalidUrl)) {
			   System.out.println("INCORRECT: " + invalidUrl + " as valid should be invalid") ;
			   result = false;
		   }
	   }
	   
	   if (result) {
		   System.out.println("Testing Second Partition: Scheme Passed");
	   } else {
		   System.out.println("Testing Second Partition: Valid Scheme Failed");
	   }
	   
	   System.out.println("Test Second Partition End");
   }
   
   public void testIsValid()
   {
       String[] scheme = {"http://",/* "ftp://", "h3t://",*/ "3ht://", "http:/", "http:", "http/", "://", ""};
       String[] authority = {"www.google.com", "go.com", "go.au", "0.0.0.0", "255.255.255.255", "256.256.256.256", "255.com", "1.2.3.4.5", "1.2.3.4.", "1.2.3", ".1.2.3.4", "go.a", "go.a1a", "go.1aa", "aaa.", ".aaa", "aaa", ""};
       String[] port = {":80", ":65535", ":0", "", ":-1", ":65636", ":65a"};
       String[] path = {"/test1", "/t1234", "/$23", "/..", "/../", "/test1/", "", "/test1/file", "/..//file", "/test1//file"};
       String[] query = {"?action=view", "?action=edit&mode=up", ""};
       
       String[] schemeFalse = {"3ht://", "http:/", "http:", "http/", "://"};
       String[] authorityFalse = {"256.256.256.256", "1.2.3.4.5", "1.2.3.4.", "1.2.3", ".1.2.3.4", "go.a", "go.a1a", "go.1aa", "aaa.", ".aaa", "aaa", ""};
       String[] portFalse = {":-1", ":65636", ":65a"};
       String[] pathFalse = {"/..", "/../", "/..//file", "/test1//file"};
       boolean testResult;
       boolean shouldBe;
       int valid = 0;
       int invalid = 0;
       int totalTests = 0;
       String url;
       UrlValidator urlValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       
       for(int i = 0; i < scheme.length; i++)
       {
           //System.out.format("i = %d\n", i);
           for(int j = 0; j < authority.length; j++)
           {
               //System.out.format("j = %d\n", j);
               for(int k = 0; k < port.length; k++)
               {
                   //System.out.format("k = %d\n", k);
                   for(int m = 0; m < path.length; m++)
                   {
                       //System.out.format("m = %d\n", m);
                       for(int n = 0; n < query.length; n++)
                       {
                           //System.out.format("n = %d\n", n);
                           url = scheme[i] + authority[j] + port[k] + path[m] + query[n];
                           //System.out.format("%s\n", url);
                           testResult = urlValidator.isValid(url);
                           shouldBe = true;
                           
                           for(int x = 0; x < schemeFalse.length; x++)
                           {
                               if(scheme[i] == schemeFalse[x])
                               {
                                   shouldBe = false;
                                   break;
                               }
                           }
                           
                           if(shouldBe)
                           {
                               for(int y = 0; y < authorityFalse.length; y++)
                               {
                                   if(authority[j] == authorityFalse[y])
                                   {
                                       shouldBe = false;
                                       break;
                                   }
                               }
                           }
                           
                           if(shouldBe)
                           {
                               for(int z = 0; z < portFalse.length; z++)
                               {
                                   if(port[k] == portFalse[z])
                                   {
                                       shouldBe = false;
                                       break;
                                   }
                                   
                               }
                           }
                           
                           if(shouldBe)
                           {
                               for(int a = 0; a < pathFalse.length; a++)
                               {
                                   if(path[m] == pathFalse[a])
                                   {
                                       shouldBe = false;
                                       break;
                                   }
                                   
                               }
                           }
                           
                           if(testResult == shouldBe)
                           {
                               //System.out.format("CORRECT: %s\n", url);
                               ;
                           }
                           else
                           {
                               if (testResult) 
                               {      
                                   System.out.format("INCORRECT: %s tests as Valid should be Invalid\n", url);
                                   valid++;
                               }
                               else 
                               {
                                   System.out.format("INCORRECT: %s tests as Invalid should be Valid\n", url);
                                   invalid++;
                               }
                           }
                           
                           totalTests++;
                       }
                   }
               }
           }
       }
       
       System.out.format("Total Tests = %d\n", totalTests);
       System.out.format("Valid Tests = %d\n", valid);
       System.out.format("Invalid Tests = %d\n", invalid);
   }
   


}
