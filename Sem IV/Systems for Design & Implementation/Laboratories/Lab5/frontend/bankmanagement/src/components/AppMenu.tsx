import { AppBar, Box, Button, Toolbar, Typography, colors } from "@mui/material";
import { Link, useLocation } from "react-router-dom";
import LocalLibraryIcon from "@mui/icons-material/LocalLibrary";
import AddIcon from '@mui/icons-material/Add';
import SummarizeIcon from '@mui/icons-material/Summarize';
import HomeIcon from '@mui/icons-material/Home';


export const AppMenu = () => {
    const location = useLocation();
    const path = location.pathname;

    return (
        // set a green background color for the Box

        <Box sx={{ flexGrow: 1 }}>
            <AppBar position="static" sx={{ marginBottom: "20px", backgroundColor: colors.pink[500] }}>
                <Toolbar>
                    <Button
                        to="/"
                        component={Link}
                        color="inherit"
                        sx={{ mr: 2 }}
                        startIcon={<HomeIcon />}>
                    </Button>
                    <Typography variant="h6" component="div" sx={{ mr: 5 }}>
                        Bank Management
                    </Typography>
                    <Button
                        variant={path.startsWith("/customer") ? "outlined" : "text"}
                        to="/customer"
                        component={Link}
                        color="inherit"
                        sx={{ mr: 4 }}
                        startIcon={<LocalLibraryIcon />}>
                        Customers
                    </Button>
                    <Button
                        variant={path.startsWith("/customer/add") ? "outlined" : "text"}
                        to="/customer/add"
                        component={Link}
                        color="inherit"
                        sx={{ mr: 4 }}
                        startIcon={<AddIcon />}>
                        Add Customer
                    </Button>
                    <Button
                        variant={path.startsWith("/customer/by-total-balance") ? "outlined" : "text"}
                        to="/customer/by-total-balance"
                        component={Link}
                        color="inherit"
                        sx={{ mr: 4 }}
                        startIcon={<SummarizeIcon />}>
                        Total Balance
                    </Button>
                </Toolbar>
            </AppBar>
        </Box>
    )
}