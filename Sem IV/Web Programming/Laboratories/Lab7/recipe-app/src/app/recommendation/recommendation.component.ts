import { Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Router } from '@angular/router';

interface Recipe {
  name: string;
  author: string;
  type: string;
  recipe: string;
}

@Component({
  selector: 'app-recommendation',
  templateUrl: './recommendation.component.html',
  styleUrls: ['./recommendation.component.css']
})
export class RecommendationComponent implements OnInit {
  recipe: Recipe = {
    name: '',
    author: '',
    type: '',
    recipe: ''
  };

  constructor(private http: HttpClient, private router: Router) { }

  ngOnInit() {
    this.getRandomRecipe();
  }

  getRandomRecipe() {
    this.http.get<Recipe>('recommendation.php').subscribe(
      data => {
        this.recipe = data;
      },
      error => {
        console.error('Error getting random recipe:', error);
      }
    );
  }

  goBack() {
    // Navigate back to the menu page
    this.router.navigate(['/menu']);
  }
}
