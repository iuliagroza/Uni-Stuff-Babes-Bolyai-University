import { Component } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Router } from '@angular/router';

interface Recipe {
  name: string;
  author: string;
  type: string;
  recipe: string;
}

@Component({
  selector: 'app-add',
  templateUrl: './add.component.html',
  styleUrls: ['./add.component.css']
})
export class AddComponent {
  recipe: Recipe = {
    name: '',
    author: '',
    type: '',
    recipe: ''
  };
  message: string = '';
  isError: boolean = false;

  constructor(private http: HttpClient, private router: Router) { }

  submitForm() {
    this.http.post('add.php', this.recipe).subscribe(
      () => {
        // Recipe added successfully, navigate back to the menu page
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
        console.error('Error adding recipe:', error);
      }
    );
  }

  goBack() {
    // Navigate back to the menu page
    this.router.navigate(['/menu']);
  }
}
