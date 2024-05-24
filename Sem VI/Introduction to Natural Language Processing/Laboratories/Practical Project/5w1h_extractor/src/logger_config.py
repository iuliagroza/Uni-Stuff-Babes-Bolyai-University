import logging

def setup_logger(name, log_file, level=logging.INFO):
    handler = logging.FileHandler(log_file)        
    handler.setFormatter(logging.Formatter('%(asctime)s %(message)s'))

    logger = logging.getLogger(name)
    logger.setLevel(level)
    logger.addHandler(handler)

    return logger
