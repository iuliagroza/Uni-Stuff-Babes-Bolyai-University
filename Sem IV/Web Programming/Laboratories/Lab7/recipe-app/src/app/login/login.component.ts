import { Component } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent {
  username: string = 'admin';
  password: string = 'testpwd123';
  error: string = '';

  constructor(private http: HttpClient) { }

  login() {
    // Perform login logic here
    const loginData = {
      username: this.username,
      password: this.password
    };

    this.http.post<any>('http://localhost/lab7/index.php', loginData).subscribe(
      response => {
        // Handle successful login
        console.log('Login success:', response);
      },
      error => {
        // Handle login error
        console.error('Login error:', error);
      }
    );
  }
}
