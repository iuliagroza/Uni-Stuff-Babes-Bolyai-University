import { AppBar, Box, Button, Toolbar, Typography, colors } from "@mui/material";
import { Link } from "react-router-dom";
import HomeIcon from '@mui/icons-material/Home';

export const HomeMenu = () => {
    return (
        <Box sx={{ flexGrow: 1 }}>
            <AppBar position="static" sx={{ marginBottom: "20px", backgroundColor: colors.pink[500] }}>
                <Toolbar>
                    <Button
                        to="/admin"
                        component={Link}
                        color="inherit"
                        sx={{ mr: 2 }}
                        startIcon={<HomeIcon />}>
                    </Button>
                    <Typography variant="h6" component="div" sx={{ mr: 5 }}>
                        Vacation Rentals
                    </Typography>
                </Toolbar>
            </AppBar>
        </Box >
    )
}