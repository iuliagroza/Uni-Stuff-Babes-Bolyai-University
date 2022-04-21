# Import and initialize the pygame library
import pygame


class GUI:
    @staticmethod
    def main_window(screen, button_easy, button_medium, button_hard):
        screen.fill((29, 57, 99))

        pygame.font.init()  # you have to call this at the start,
        # if you want to use this module.
        my_font = pygame.font.SysFont('DroidSans', 45)
        welcome = my_font.render('WELCOME TO PLANES!', False, (255, 255, 255))
        ai_option = my_font.render('Choose the difficulty of the game:', False, (255, 255, 255))
        screen.blit(welcome, (310, 50))
        screen.blit(ai_option, (250, 150))

        easy = my_font.render('Easy', False, (255, 255, 255))
        pygame.draw.rect(screen, [15, 15, 61], button_easy)  # draw button
        screen.blit(easy, (240, 270))

        medium = my_font.render('Medium', False, (255, 255, 255))
        pygame.draw.rect(screen, [15, 15, 61], button_medium)  # draw button
        screen.blit(medium, (445, 270))

        hard = my_font.render('Hard', False, (255, 255, 255))
        pygame.draw.rect(screen, [15, 15, 61], button_hard)  # draw button
        screen.blit(hard, (690, 270))

    def place_planes(self, screen):
        screen.fill((29, 57, 99))

        pygame.font.init()  # you have to call this at the start,
        # if you want to use this module.
        my_font = pygame.font.SysFont('DroidSans', 26)
        msg = my_font.render("""The computer has placed its planes. Now it's your turn! Place three planes on the board so we can start the game.""", False, (255, 255, 255))
        msg2 = my_font.render("""A plane cannot overlap with another plane and it should not outrun your board.""", False, (255, 255, 255))
        screen.blit(msg, (35, 25))
        screen.blit(msg2, (35, 45))
        self.draw_grid(screen)

    @staticmethod
    def draw_grid(screen):
        block_size = 30  # Set the size of the grid block
        for x in range(350, 650, block_size):
            for y in range(100, 400, block_size):
                rect = pygame.Rect(x, y, block_size, block_size)
                pygame.draw.rect(screen, [255, 255, 255], rect, 1)

    def start(self):
        pygame.init()

        # Set up the drawing window and its title
        screen = pygame.display.set_mode([1000, 500])
        pygame.display.set_caption('Planes')

        button_easy = pygame.Rect(200, 250, 150, 70)
        button_medium = pygame.Rect(425, 250, 150, 70)
        button_hard = pygame.Rect(650, 250, 150, 70)

        # Run until the user asks to quit
        running = True
        app_state = 1
        while running:
            # Did the user click the window close button?
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

                if event.type == pygame.MOUSEBUTTONDOWN:
                    mouse_pos = event.pos  # gets mouse position

                    # checks if mouse position is over the button

                    if button_easy.collidepoint(mouse_pos):
                        ai_option = 1
                        app_state = 2

                    if button_medium.collidepoint(mouse_pos):
                        ai_option = 2
                        app_state = 2

                    if button_hard.collidepoint(mouse_pos):
                        ai_option = 3
                        app_state = 2

            if app_state == 1:
                self.main_window(screen, button_easy, button_medium, button_hard)
            elif app_state == 2:
                self.place_planes(screen)

            # Flip the display
            pygame.display.flip()

        # Done! Time to quit.
        pygame.quit()
