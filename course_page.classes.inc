<?php

class CourseObjectPage extends CourseObjectNode {
	
	function getNodeTypes(){
		return array('page');
	}
	/**
	 * Create the page node and set it as this objects instance.
	 */
	public function create(){
		parent::create(); // I probably could omit this function, but I'll leave it for now
	}
	
	function optionsDefinition(){
		$defaults = parent::optionsDefinition();
		$defaults['page_tracking'] = 'true';
		
		return $defaults;
	}
	
	function optionsForm(&$form, &$form_state){
		$config = $this->optionsDefinition();
		parent::optionsForm($form, $form_state); // call parent method
		
		$form['page_tracking'] = array(
			'#title' => t('Track if user viewed?'),
			'#type' => 'select',
			'#options' => array(
				'true' => 'Track',
				'false' => 'Not Tracked',
			),
			'#default_value' => $config['page_tracking'],
		);
	}
	
	/**
	 * Grade (track) the page based on fullfilment data
	 */
	function grade() {
		$nid = $this->node->nid; // get current node id
		$viewed = $this->getFulfillment()->getOption('page_fulfillment'); // get the current page fulfillment value
		
		// is this page tracked?
		if($this->getOption('page_tracking') == 'true'){
			//has the user viewed?
			if(!$viewed){
				// no?  then mark it viewed...
				$this->getFulfillment()->setComplete(1)->save();
			}
		}
	}
}

?>