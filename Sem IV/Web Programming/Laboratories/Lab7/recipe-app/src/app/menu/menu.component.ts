import { Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';

interface Recipe {
  Rid: number;
  Name: string;
  Author: string;
  Recipe: string;
}

@Component({
  selector: 'app-menu',
  templateUrl: './menu.component.html',
  styleUrls: ['./menu.component.css']
})
export class MenuComponent implements OnInit {
  recipes: Recipe[] = [];
  filter: string = 'All';
  isLoading: boolean = false;

  constructor(private http: HttpClient) { }

  ngOnInit() {
    this.getRecipesByType('All');
  }

  getRecipesByType(recipeType: string) {
    this.isLoading = true;

    this.http.post<Recipe[]>('ajax.php', { type: recipeType }).subscribe(
      response => {
        this.recipes = response;
        this.filter = recipeType;
        this.isLoading = false;
      },
      error => {
        console.error('Error retrieving recipes:', error);
        this.isLoading = false;
      }
    );
  }

  deleteRecipe(recipeId: number) {
    const confirmation = confirm('Are you sure you want to delete this recipe?');
    if (confirmation) {
      this.http.post('delete.php', { id: recipeId }).subscribe(
        () => {
          // Recipe deleted successfully, refresh the recipe list
          this.getRecipesByType(this.filter);
        },
        error => {
          console.error('Error deleting recipe:', error);
        }
      );
    }
  }

  editRecipe(recipeId: number) {
    // Redirect to the edit page with the recipeId
    // Replace 'edit' with the actual route/path for the edit component
    // You may need to configure the Angular router for this navigation to work
    // For example: this.router.navigate(['edit', recipeId]);
  }

  logout() {
    // Logout logic
    // Replace 'logout-api-endpoint' with the actual URL of the logout API endpoint
    this.http.post('menu.php', {}).subscribe(
      () => {
        // Redirect to the login page
        // Replace 'login' with the actual route/path for the login component
        // You may need to configure the Angular router for this navigation to work
        // For example: this.router.navigate(['login']);
      },
      error => {
        console.error('Error logging out:', error);
      }
    );
  }

  getRandomRecipe() {
    // Redirect to the random recipe page
    // Replace 'recommendation' with the actual route/path for the recommendation component
    // You may need to configure the Angular router for this navigation to work
    // For example: this.router.navigate(['recommendation']);
  }
}
