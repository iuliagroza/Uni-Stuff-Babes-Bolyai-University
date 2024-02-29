import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { HttpClient } from '@angular/common/http';

interface Recipe {
  id: string;
  name: string;
  author: string;
  type: string;
  recipe: string;
}

@Component({
  selector: 'app-edit',
  templateUrl: './edit.component.html',
  styleUrls: ['./edit.component.css']
})
export class EditComponent implements OnInit {
  recipe: Recipe = {
    id: '',
    name: '',
    author: '',
    type: '',
    recipe: ''
  };
  message: string = '';
  isError: boolean = false;

  constructor(private route: ActivatedRoute, private http: HttpClient, private router: Router) { }

  ngOnInit() {
    this.route.queryParams.subscribe(params => {
      const id = params['id'];
      if (id) {
        this.getRecipe(id);
      } else {
        // No recipe ID provided
        this.router.navigate(['/menu']);
      }
    });
  }

  getRecipe(id: string) {
    this.http.get<Recipe>('edit.php?id=' + id).subscribe(
      data => {
        this.recipe = data;
      },
      error => {
        this.isError = true;
        if (error.error instanceof ErrorEvent) {
          // Client-side error
          this.message = 'An error occurred: ' + error.error.message;
        } else {
          // Server-side error
          this.message = 'An error occurred. Please try again later.';
        }
        console.error('Error getting recipe:', error);
      }
    );
  }

  submitForm() {
    this.http.post('edit.php', this.recipe).subscribe(
      () => {
        // Recipe updated successfully, navigate back to the menu page
        this.router.navigate(['/menu']);
      },
      error => {
        this.isError = true;
        if (error.error instanceof ErrorEvent) {
          // Client-side error
          this.message = 'An error occurred: ' + error.error.message;
        } else {
          // Server-side error
          this.message = 'An error occurred. Please try again later.';
        }
        console.error('Error updating recipe:', error);
      }
    );
  }

  goBack() {
    // Navigate back to the menu page
    this.router.navigate(['/menu']);
  }
}
