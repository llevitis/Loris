INSERT INTO LorisMenu (Label, Link, Parent, OrderNumber) VALUES
    ('Imaging QC', 'quality_control/', (SELECT ID FROM LorisMenu as L WHERE Label='Tools'), 10);