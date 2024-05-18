package org.example.features.search;

import net.serenitybdd.junit.runners.SerenityRunner;
import net.thucydides.core.annotations.Managed;
import net.thucydides.core.annotations.Steps;
import org.example.steps.serenity.FrontendMastersSteps;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.openqa.selenium.WebDriver;

import static org.hamcrest.CoreMatchers.containsString;
import static org.junit.Assert.assertThat;
import static org.junit.Assert.assertTrue;

@RunWith(SerenityRunner.class)
public class FrontendMastersLoginTest {
    @Managed
    WebDriver driver;
    
    @Steps
    FrontendMastersSteps steps; 
    
    @Test
    public void testLoginIncorrect() {
        steps.openFrontendmastersHomePage();
        steps.pressLogin(); 
        steps.submitLogin("admin", "admin");
        String errorMessage = steps.loginError();
        assertThat(errorMessage, containsString("That wasn't correct. Try again?"));
    }
    
    @Test 
    public void testLoginCorrect() {
        steps.openFrontendmastersHomePage();
        steps.pressLogin();
        steps.submitLogin("andrei.albert2708@gmail.com", "Gabriela23!@#$"); 
        assertTrue(steps.isAtDashboardPage());
    }
}
