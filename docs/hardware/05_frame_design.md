# Frame Design and Assembly Guide

## 1. Frame Design Specifications

### Design Requirements
- Total weight: aim for < 85g
- Frame dimensions: Standard eyewear size (135-145mm temple length)
- Component housing requirements:
  * Right temple: ESP32-S3, OLED, battery
  * Left temple: Battery, bone conduction speaker
  * Front frame: Camera, touch sensors
  * Hidden microphone placement

### Material Selection
- Primary frame: PETG or Nylon (recommended)
  * Better heat resistance than PLA
  * More durable for daily wear
  * Flexible enough for comfort
- Optional: TPU for comfort pads
- Clear PMMA for optical elements

## 2. Component Housing Design

### Right Temple Design
```
Dimensions:
- Length: 140mm
- Width: 8mm
- Height: 12mm
- Internal cavity: 6mm x 10mm

Component Layout (front to back):
1. OLED display (25mm x 15mm cavity)
2. ESP32-S3 module (20mm x 18mm cavity)
3. Battery compartment (30mm x 6mm x 10mm)
4. Wire routing channel (2mm diameter)
```

### Left Temple Design
```
Dimensions:
- Length: 140mm
- Width: 8mm
- Height: 12mm
- Internal cavity: 6mm x 10mm

Component Layout (front to back):
1. Bone conduction speaker mount
2. Battery compartment
3. Wire routing channel
```

### Front Frame Design
```
Dimensions:
- Total width: ~142mm
- Bridge width: 18mm
- Lens height: 45mm
- Lens width: 52mm

Features:
1. Camera housing (center-top)
2. Touch sensor strip integration
3. Wire routing channels
4. Ventilation holes
```

## 3. 3D Printing Guidelines

### Print Settings
```
General Settings:
- Layer height: 0.12mm
- Wall thickness: 1.2mm
- Infill: 20% (gyroid pattern)
- Support: Yes (for overhangs)
- Build plate adhesion: Brim

Temperature Settings:
- PETG:
  * Nozzle: 235-245°C
  * Bed: 80-85°C
- Nylon:
  * Nozzle: 245-260°C
  * Bed: 90-100°C
```

### Post-Processing
1. Support Removal:
   - Use needle-nose pliers
   - Fine-tune with hobby knife
   - Sand contact points

2. Surface Finishing:
   - Progressive sanding (220 → 400 → 800 → 1000 grit)
   - Optional: Spray filler primer
   - Final polish for smooth finish

## 4. Component Installation Guide

### Wiring Layout
```
Main Wire Routing:
1. Right Temple:
   ESP32-S3 → OLED → Battery → Front Frame
2. Left Temple:
   Battery → Bone Conduction → Front Frame
3. Front Frame:
   Camera → Touch Sensors → Temple Connections
```

### Installation Steps

1. Prepare Components:
```
a) Pre-test all components
b) Pre-cut all wires to length
c) Pre-tin all connections
d) Prepare heat shrink tubes
```

2. Right Temple Assembly:
```
1. Install ESP32-S3:
   - Apply thermal paste
   - Secure with M2 screws
   - Connect power lines

2. Mount OLED:
   - Secure display bracket
   - Route I2C cables
   - Test connection

3. Install Battery:
   - Place battery protection circuit
   - Secure battery with foam padding
   - Route power cables
```

3. Left Temple Assembly:
```
1. Mount Bone Conduction Speaker:
   - Secure mounting bracket
   - Route audio cables
   - Add dampening material

2. Install Battery:
   - Same procedure as right temple
   - Ensure weight balance
```

4. Front Frame Assembly:
```
1. Camera Installation:
   - Mount camera module
   - Secure lens assembly
   - Route data cables

2. Touch Sensor Integration:
   - Install touch sensor strip
   - Route control wires
   - Test sensitivity
```

## 5. Final Assembly

### Connection Verification
```python
def verify_connections():
    components = {
        'esp32': {'power': False, 'data': False},
        'oled': {'i2c': False},
        'camera': {'power': False, 'data': False},
        'audio': {'power': False, 'signal': False},
        'touch': {'power': False, 'signal': False}
    }
    
    # Verification steps
    for component, checks in components.items():
        print(f"Verifying {component}...")
        for check_type in checks:
            # Implement verification logic
            pass
```

### Weatherproofing
1. Sealing Steps:
   - Apply silicone sealant around joints
   - Use UV-curable resin for clear parts
   - Add water-resistant coating

2. Ventilation:
   - Maintain air flow channels
   - Install hydrophobic mesh over vents
   - Add moisture absorbing material

### Weight Distribution
1. Balance Check:
   - Measure weight distribution
   - Add counterweights if needed
   - Verify comfort on nose bridge

2. Adjustments:
   - Fine-tune temple tension
   - Adjust nose pads
   - Test fit with head movement

## 6. Testing and Quality Control

### Physical Tests
- [ ] Drop test from 1m height
- [ ] Flex test (1000 cycles)
- [ ] Temperature test (0-40°C)
- [ ] Water resistance check
- [ ] Weight distribution check
- [ ] Comfort test (2-hour wear)

### Electronic Tests
- [ ] Power consumption monitoring
- [ ] Heat distribution check
- [ ] Signal interference test
- [ ] Battery life verification
- [ ] Display visibility test
- [ ] Audio quality check

### Final Checklist
1. Safety Checks:
   - No sharp edges
   - All components secure
   - No exposed wiring
   - Battery protection verified

2. Functionality:
   - All systems operational
   - No interference between components
   - Stable connectivity
   - Clear audio output
   - Responsive touch controls

3. User Comfort:
   - Balanced weight distribution
   - Comfortable fit
   - Easy to put on/remove
   - No pressure points

## 7. Maintenance Guide

### Regular Maintenance
1. Daily:
   - Clean lenses/sensors
   - Check for loose components
   - Verify charging contacts

2. Weekly:
   - Check all connections
   - Test all functions
   - Clean ventilation ports

3. Monthly:
   - Full system diagnostic
   - Update firmware if needed
   - Check battery health
   - Inspect frame integrity

### Troubleshooting Common Issues
1. Power Issues:
   - Check battery connections
   - Verify charging circuit
   - Test power distribution

2. Display Problems:
   - Check I2C connections
   - Verify OLED mounting
   - Test display driver

3. Audio Issues:
   - Verify bone conduction contact
   - Check audio connections
   - Test amplifier circuit

4. Connectivity Problems:
   - Check antenna placement
   - Verify ESP32-S3 connections
   - Test WiFi signal strength