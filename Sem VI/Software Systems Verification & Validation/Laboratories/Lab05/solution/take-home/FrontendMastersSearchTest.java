package org.example.features.search;


import net.serenitybdd.junit.runners.SerenityRunner;
import net.thucydides.core.annotations.Managed;
import net.thucydides.core.annotations.Steps;
import org.example.steps.serenity.FrontendMastersSteps;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.openqa.selenium.WebDriver;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

@RunWith(SerenityRunner.class)

public class FrontendMastersSearchTest {
    @Managed
    WebDriver driver;
    
    
    @Steps
    FrontendMastersSteps steps;
    
    @Test 
    public void searchValidInput() {
        this.steps.openFrontendmastersHomePage(); 
        this.steps.searchItem("Javascript");
        assertFalse(steps.searchResultIsEmpty());
    }

    @Test
    public void searchInvalidInput() {
        this.steps.openFrontendmastersHomePage();
        this.steps.searchItem("sdfsdf");
        assertTrue(steps.searchResultIsEmpty());
    }
}
