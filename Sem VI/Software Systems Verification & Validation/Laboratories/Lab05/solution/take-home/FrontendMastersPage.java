package org.example.pages;

import net.serenitybdd.core.pages.WebElementFacade;
import net.thucydides.core.annotations.DefaultUrl;
import net.thucydides.core.pages.PageObject;
import org.openqa.selenium.support.FindBy;

import java.util.List;

@DefaultUrl("https://frontendmasters.com/")
public class FrontendMastersPage extends PageObject {
    @FindBy(className = "FM-BGI-Link-Search")
    private WebElementFacade searchBtn; 
    
    @FindBy(className = "login")
    private WebElementFacade loginBtn; 
    
    @FindBy(id = "username")
    private WebElementFacade nameInput;
    
    @FindBy(id = "password")
    private WebElementFacade passwordInput;

    @FindBy(css = ".Button.ButtonRed.ButtonLarge")
    private WebElementFacade submitLoginBtn;

    @FindBy(css = ".Message.MessageAlert")
    private WebElementFacade loginErrorMessage;

    @FindBy(css = "input[type='search'][placeholder='Search']")
    private WebElementFacade searchInput;

    @FindBy(css = "ul > li.ResultListItem")
    private List<WebElementFacade> searchResults;
    
    public void press_login() {
        this.loginBtn.click();
    }
    
    public void submit_login() {
        this.submitLoginBtn.click();
    }
    
    public void enter_username(String username) {
        this.nameInput.type(username);
    }
    
    public void enter_password(String password) {
        this.passwordInput.type(password);
    }
    
    public void perform_login(String username, String password) {
        System.out.println(this.nameInput);
        this.enter_username(username);
        this.enter_password(password);
        this.submit_login();
    }

    public String getLoginErrorMessage() {
        return loginErrorMessage.isVisible() ? loginErrorMessage.getText() : "";
    }
    
    public boolean isAtDashboard() {
        return getDriver().getCurrentUrl().contains("/dashboard");
    }
    
    public void searchItem(String item) {
        this.searchBtn.click();
        this.searchInput.typeAndEnter(item);
    }
    
    public boolean searchResultIsEmpty() {
        return this.searchResults.isEmpty();
    }
}
